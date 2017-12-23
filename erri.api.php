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
 * Provide an array of information on all delete forms for which you want referential
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
 *   'target_type' => Required.  The machine name of the entity type being deleted.
 *   'is_delete_form' => If the form ID is used for various versions of the form,
 *         this specifies the name of the function to call to determine if the form
 *         is in its delete mode.  This function will be passed the form array.
 *
 *   @see erri.inc
 */
function hook_erri_info() {
  return array(
    'my_delete_form_using_confirm_form' => array(
      'entity' => 'my_function_to_get_the_entity',
      'target_type' => 'my_entity_type',
      'is_delete_form' => 'my_function_to_determine_if_this_is_the_delete_version_of_the_form',
    ),
    'my_multi_delete_form_using_confirm_form' => array(
      'entities' => 'my_function_to_get_array_of_entities',
      'target_type' => 'my_entity_type',
      'is_delete_form' => 'my_function_to_determine_if_this_is_the_delete_version_of_the_form',
    ),
  );
}

/**
 * Provide additional fields to Entity Reference Referential Integrity to check.
 * The hook should return an array by field name with each field type either
 * entityreference or taxonomy_term_reference.  This will require overriding the
 * actual field type to indicate to what the column specified as the referring
 * column is actually pointing.  Note that these fields must be fields defined
 * through the fields API.
 *
 * @return array An array of fields in the same format as would be returned by
 *   field_read_fields().
 */
function hook_erri_reference_fields() {
  $fields = array(
    'my_field_name' => array(
      'type' => 'entityreference',
      'settings' => array(
        'target_type' => 'node',
        'handler_settings' => array(
          'target_bundles' => array('my_bundle', 'my_other_bundle'),
        ),
      ),
      'storage' => array(
        'details' => array(
          'sql' => array(
            'FIELD_LOAD_CURRENT' => array(
              'field_data_field_my_field_name' => array(
                'target_id' => 'field_my_field_name_target_id',
              ),
            ),
          ),
        ),
      ),
    ),
  );
  $other_fields = field_read_fields(array('type' => 'my_field_type'));
  foreach ( $other_fields as &$field ) {
    $field['type'] = 'entityreference'; // Override the field type to have it checked.
    $field['settings']['target_type'] = 'node'; // Set this if it isn't set in the field definition.
    foreach ( array_keys($field['storage']['details']['sql']['FIELD_LOAD_CURRENT']) as $table ) {
      // ERRI only uses the reference column, so override the 'table' array with just one column.
      $field['storage']['details']['sql']['FIELD_LOAD_CURRENT'][$table] = array('target_id' => 'field_the_entity_reference_column_name');
    }
  }
  return $fields + $other_fields;
}

/**
 * @} End of "addtogroup hooks".
 */
