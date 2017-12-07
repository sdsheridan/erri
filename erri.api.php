<?php
/**
 * @file
 * Hooks provided by the Entity Reference Referential Integrity API.
 */

/**
 * @addtogroup hooks
 * @{
 */

/**
 * Provide an array of information on all delete form for which you want referential
 * integrity checked.  Each element of the return array is itself an array, keyed
 * on the form ID of the delete form it is describing.  Each sub element can have
 * the following key-value pairs:
 *   'entity' => Required for single-entity delete forms, and cannot be present for
 *         multi-entity delete forms.  Specifies the function to call to return the
 *         entity that is being deleted.  This function will be passed the form array.
 *   'entities' => Required for multi-entity delete forms, and cannot be present for
 *         single-entity delete forms.  Specifies the function to call to return an
 *         array with the keys being the entity IDs that are being deleted.  This 
 *         function will be passed the form array.
 *   'entity_id' => Required.  The name of the object property holding the entity ID.
 *   'target_type' => Required.  The machine name of the entity type being deleted.
 *   'bundles' => TRUE if the entity type uses bundles, as is the case with nodes.
 *   'is_delete_form' => If the form ID is used for various versions of the form,
 *         this specifies the name of the function to call to determine if the form
 *         is in its delete mode.  This function will be passed the form array.
 *   'entity_load_function' => Required.  The name of the function that will load
 *         the entity from its ID.
 *   'name_field' => Required.  The name of the object property that holds the entity's
 *         human-readable name.
 *   'type_name' => Required for multi-entity delete forms.  The human-readable name
 *         of the entity type.
 *   'use_id_in_name' => TRUE if the entity ID should be shown along with the entity
 *         name in the output for multi-entity delete forms.  Set to TRUE if entity's
 *         can have non-unique names.
 * 
 *   @see erri.inc
 */
function hook_erri_info() {
  return array(
    'my_delete_form_using_confirm_form' => array(
      'entity' => 'my_function_to_get_the_entity',
      'entity_id' => 'eid',
      'target_type' => 'my_entity_type',
      'bundles' => FALSE,
      'is_delete_form' => 'my_function_to_determine_if_this_is_the_delete_version_of_the_form',
      'entity_load_function' => 'my_entity_load_function',
      'name_field' => 'name',
    ),
    'my_multi_delete_form_using_confirm_form' => array(
      'entities' => 'my_function_to_get_array_of_entities',
      'entity_id' => 'eid',
      'target_type' => 'my_entity_type',
      'bundles' => FALSE,
      'is_delete_form' => 'my_function_to_determine_if_this_is_the_delete_version_of_the_form',
      'entity_load_function' => 'my_entity_load_function',
      'name_field' => 'name',
      'type_name' => t('the human-readable name of the entity type'),
      'use_id_in_name' => TRUE,
    ),
  );
}

/**
 * @} End of "addtogroup hooks".
 */
