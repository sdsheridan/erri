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
      'target_type' => 'node',
    ),
    'node_admin_content' => array(
      'entities' => 'erri_node_entities',
      'target_type' => 'node',
      'is_delete_form' => 'erri_node_entities_delete',
    ),
    'user_cancel_confirm_form' => array(
      'entity' => 'erri_user_entity',
      'target_type' => 'user',
    ),
    'user_multiple_cancel_confirm' => array(
      'entities' => 'erri_user_entities',
      'target_type' => 'user',
    ),
    'taxonomy_form_term' => array(
      'entity' => 'erri_taxonomy_term_entity',
      'target_type' => 'taxonomy_term',
      'is_delete_form' => 'erri_taxonomy_term_delete',
    ),
    'taxonomy_manager_form' => array(
      'entities' => 'erri_taxonomy_term_entities',
      'target_type' => 'taxonomy_term',
      'is_delete_form' => 'erri_taxonomy_term_delete',
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
 * @param array $form The term admin form array.
 * @return bool TRUE if this is the delete form of the term-admin form.
 */
function erri_taxonomy_term_delete($form) {
  return !empty($form['delete']['#value']);
}

