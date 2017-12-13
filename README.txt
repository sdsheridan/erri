Entity Reference Referential Integrity
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

This module solves the problem of deleting parent entities (nodes, taxonomy
terms, users, etc.) that are referred to by other entities through taxonomy term
reference or entity reference fields.  Drupal will not prevent a user from
deleting such 'parent entities', but this module will.  It hooks into various
entity delete forms, and does a check of the entity or entities about to be
deleted as to whether or not they are referred to by any other entities, and if
so, disables the delete button on the form if any of the referring fields are
required, or alternatively where they are all optional, changes the text of the
delete button to indicate all referring fields will be set to empty, and shows
the referrers (the child entities) to the user.

The module already handles node, taxonomy term, and user delete forms, both
single and multi-versions (including taxonomy manager's delete), and has an API
to hook into for other modules that use the Drupal confirm_form() function to
create their delete forms, or at least have the [description][#markup] element
and the [actions][submit] button used for the delete (see
https://api.drupal.org/api/drupal/modules%21system%21system.module/function/confirm_form/7.x).
Note that this module currently implements 'Restrict' referential integrity
where any of the referring fields' settings are set as 'Required', and 'Set
Null' if all of the referring fields' settings are set as not required.
'Cascade' is not (yet) implemented.

Otherwise, a module can also call the function erri_get_child_entities, passing
it the specified parameters, to get a list of child entities for a particular
parent, and then act accordingly.   For example:

    $fields = erri_get_child_entities('node', $parent->nid, TRUE, 'customer');
    if ( !empty($fields) ) {
      foreach ( $fields as $field_name => $children ) {
        // $children is an array with each element an array of entity_type, bundle,
        // entity_id, etc. that all point to node $parent through field $field_name.
        ...
      }
    }


Installation
~~~~~~~~~~~~
Install this module like any other, and activate it.  There's nothing else to
do.  The module will begin working immediately.
