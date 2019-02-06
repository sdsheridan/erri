<?php

/**
 * Include file for erri.
 */

/**
 * Implements hook_erri_info().
 */
function erri_erri_info() {
  return array(
    'node_delete_confirm' => array(
      'entity' => '_erri_get_node_entity',
      'target_type' => 'node',
      'candidates' => '_erri_get_candidates',
    ),
    'node_admin_content' => array(
      'entities' => '_erri_get_node_entities',
      'target_type' => 'node',
      'is_delete_form' => '_erri_is_node_entities_delete',
      'candidates' => '_erri_get_candidates',
    ),
    'user_cancel_confirm_form' => array(
      'entity' => '_erri_get_user_entity',
      'target_type' => 'user',
      'candidates' => '_erri_get_candidates',
    ),
    'user_multiple_cancel_confirm' => array(
      'entities' => '_erri_get_user_entities',
      'target_type' => 'user',
      'candidates' => '_erri_get_candidates',
    ),
    'taxonomy_form_term' => array(
      'entity' => '_erri_get_taxonomy_term_entity',
      'target_type' => 'taxonomy_term',
      'is_delete_form' => '_erri_is_taxonomy_term_delete',
      'candidates' => '_erri_get_candidates',
    ),
    'taxonomy_manager_form' => array(
      'entities' => '_erri_get_taxonomy_term_entities',
      'target_type' => 'taxonomy_term',
      'is_delete_form' => '_erri_is_taxonomy_term_delete',
      'candidates' => '_erri_get_candidates',
    ),
  );
}

/**
 * Entity handler for single-node delete from.
 * @param array $form The node delete form array.
 * @return object The node being deleted.
 */
function _erri_get_node_entity($form) {
  return $form['#node'];
}

/**
 * Entity handler for multi-node delete from.
 * @param array $form The node delete form array.
 * @return array The array of node being deleted.
 */
function _erri_get_node_entities($form) {
  return $form['nodes'];
}

/**
 * Node-admin delete form handler.
 * @param array $form
 * @return bool TRUE if this is the delete form of the node-admin form.
 */
function _erri_is_node_entities_delete($form) {
  return !empty($form['operation']['#value']) && $form['operation']['#value'] == 'delete';
}

/**
 * Get candidates for replacements for nodes, taxonomy terms, and users.
 * @param string $entity_type The type of entity - 'node', 'taxonomy_term', or 'user'.
 * @param string $bundle For nodes, the node type; for taxonomy terms, the vocabulary; for users, empty string.
 * @param array $exclude_ids Array of ids of the entities being deleted.
 * @return array An array of options to replace the entity being deleted.
 */
function _erri_get_candidates($entity_type, $bundle, $exclude_ids) {
  $query = new EntityFieldQuery();
  $query->entityCondition('entity_type', $entity_type);
  switch ( $entity_type ) {
    case 'node' :
      $query->entityCondition('bundle', $bundle)
              ->propertyCondition('nid', $exclude_ids, 'NOT IN')
              ->propertyCondition('status', 1)
              ->propertyOrderBy('title');
      $item_id = 'nid';
      break;
    case 'taxonomy_term' :
      $vocab = taxonomy_vocabulary_machine_name_load($bundle);
      $query->propertyCondition('vid', $vocab->vid)
              ->propertyCondition('tid', $exclude_ids, 'NOT IN')
              ->propertyOrderBy('weight');
      $item_id = 'tid';
      break;
    case 'user' :
      $query->propertyCondition('uid', $exclude_ids, 'NOT IN')
              ->propertyOrderBy('name');
      $item_id = 'uid';
      break;
  }
  $result = $query->execute();
  $options = array();
  if ( !empty($result[$entity_type]) ) {
    $function = $entity_type . '_load_multiple';
    $items = $function(array_keys($result[$entity_type]));
    foreach ( $items as $item ) {
      $options[$item->$item_id] = entity_label($entity_type, $item) . ' (' . $item_id . ': ' . $item->$item_id . ')';
    }
  }
  return array_map('filter_xss', $options);
}

/**
 * Entity handler for single-user delete from.
 * @param array $form The user delete form array.
 * @return object The user being deleted.
 */
function _erri_get_user_entity($form) {
  return $form['_account']['#value'];
}

/**
 * Entity handler for multi-user delete from.
 * @param array $form The user delete form array.
 * @return array The array of users being deleted.
 */
function _erri_get_user_entities($form) {
  return $form['accounts'];
}

/**
 * Entity handler for single-term delete from.
 * @param array $form The user delete form array.
 * @return object The term being deleted.
 */
function _erri_get_taxonomy_term_entity($form) {
  return $form['#term'];
}

/**
 * Entity handler for multi-term delete from.
 * @param array $form The user delete form array.
 * @return array The terms being deleted.
 */
function _erri_get_taxonomy_term_entities($form) {
  return $form['selected_terms'];
}

/**
 * Term-admin delete form handler.
 * @param array $form The term admin form array.
 * @return bool TRUE if this is the delete form of the term-admin form.
 */
function _erri_is_taxonomy_term_delete($form) {
  return !empty($form['delete']['#value']);
}

