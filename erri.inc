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
      'entity' => 'erri_node_entity',
      'entity_id' => 'nid',
      'target_type' => 'node',
      'bundles' => TRUE,
      'entity_load_function' => 'node_load',
      'name_field' => 'title',
    ),
    'node_admin_content' => array(
      'entities' => 'erri_node_entities',
      'entity_id' => 'nid',
      'target_type' => 'node',
      'bundles' => TRUE,
      'is_delete_form' => 'erri_node_entities_delete',
      'entity_load_function' => 'node_load',
      'name_field' => 'title',
      'type_name' => t('items'),
      'use_id_in_name' => TRUE,
    ),
    'user_cancel_confirm_form' => array(
      'entity' => 'erri_user_entity',
      'entity_id' => 'uid',
      'target_type' => 'user',
      'entity_load_function' => 'user_load',
      'name_field' => 'name',
    ),
    'user_multiple_cancel_confirm' => array(
      'entities' => 'erri_user_entities',
      'entity_id' => 'uid',
      'target_type' => 'user',
      'entity_load_function' => 'user_load',
      'name_field' => 'name',
      'type_name' => t('people'),
    ),
    'taxonomy_form_term' => array(
      'entity' => 'erri_taxonomy_term_entity',
      'entity_id' => 'tid',
      'target_type' => 'taxonomy_term',
      'entity_load_function' => 'taxonomy_term_load',
      'name_field' => 'name',
      'is_delete_form' => 'erri_taxonomy_term_delete',
    ),
    'taxonomy_manager_form' => array(
      'entities' => 'erri_taxonomy_term_entities',
      'entity_id' => 'tid',
      'target_type' => 'taxonomy_term',
      'entity_load_function' => 'taxonomy_term_load',
      'name_field' => 'name',
      'is_delete_form' => 'erri_taxonomy_term_delete',
      'type_name' => t('terms'),
      'use_id_in_name' => TRUE,
    ),
  );
}

/**
 * Entity handler for single-node delete from.
 * @param array $form The node delete form array.
 * @return object The node being deleted.
 */
function erri_node_entity($form) {
  return $form['#node'];
}

/**
 * Entity handler for multi-node delete from.
 * @param array $form The node delete form array.
 * @return array The array of node being deleted.
 */
function erri_node_entities($form) {
  return $form['nodes'];
}

/**
 * Node-admin delete form handler.
 * @param array $form
 * @return bool TRUE if this is the delete form of the node-admin form.
 */
function erri_node_entities_delete($form) {
  return !empty($form['operation']['#value']) && $form['operation']['#value'] == 'delete';
}

/**
 * Entity handler for single-user delete from.
 * @param array $form The user delete form array.
 * @return object The user being deleted.
 */
function erri_user_entity($form) {
  return $form['_account']['#value'];
}

/**
 * Entity handler for multi-user delete from.
 * @param array $form The user delete form array.
 * @return array The array of users being deleted.
 */
function erri_user_entities($form) {
  return $form['accounts'];
}

/**
 * Entity handler for single-term delete from.
 * @param array $form The user delete form array.
 * @return object The term being deleted.
 */
function erri_taxonomy_term_entity($form) {
  return $form['#term'];
}

/**
 * Entity handler for multi-term delete from.
 * @param array $form The user delete form array.
 * @return array The terms being deleted.
 */
function erri_taxonomy_term_entities($form) {
  return $form['selected_terms'];
}

/**
 * Term-admin delete form handler.
 * @param array $form
 * @return bool TRUE if this is the delete form of the term-admin form.
 */
function erri_taxonomy_term_delete($form) {
  return !empty($form['delete']['#value']);
}

