Entity Reference Referential Integrity
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

This module solves the problem of deleting entities (nodes, taxonomy terms,
users, etc.) that are referred to by other entities through taxonomy term
reference or entity reference fields (see
https://www.drupal.org/project/entityreference/issues/1368386, for example).
Drupal will not prevent a user from deleting such 'target entities', but this
module will, provided some kind of delete confirmation form is used. It hooks
into various entity delete confirmation forms, and does a check of the entity or
entities about to be deleted as to whether or not they are referred to by any
other entities, and if so, shows the referring entities to the user if the
current user has view permissions on the referring entities and fields, or if
not, just that there is referring content, and either

1.  disables the delete button on the form if any of the referring fields are
    required and the user does not have permissions to bypass required field
    settings and does not have permissions to mass-change a reference target
    (see permissions below), or where the current user does not have update
    permissions on either the referring entities or referring fields, or
2.  where the referring fields are all optional and the current user has
    permissions to update both the referring entities and the referring field on
    those entities or has permissions to either bypass required contraints or
    can mass-change targets, changes the text of the delete button to indicate
    all referring fields will be set to empty or changed to a new target.

Required fields are noted with a red asterisk in the list of referrers, and in
the case where a user has insufficient permissions to update non-required
fields, the user is informed. Previous revisions are also checked.

Note that this module currently implements 'Restrict' referential integrity
where any of the referring fields' settings are set as 'Required', 'Set Null' if
all of the referring fields' settings are set as not required or the user has
permissions to bypass required constraints, and a mass-target-change upon delete
if the user has permissions.  'Cascade' is not (yet) implemented.  Changes are
recorded and can be seen in the "Recent Log Messages" report.

Permissions
~~~~~~~~~~~

The module has three special permissions, set as normal in the normal
Permissions form.  One is to bypass the required constraints for revisions, so
that users with this permission can still set referring fields to empty even if
they are required in revisions.  A second permission does that same for current
versions of content.  The third permission allows users to select a new target
for referring fields to point to when an entity is deleted.  These permissions
should be granted only to trusted roles.

API
~~~

The module already handles node, taxonomy term, and user delete forms, both
single and multi-versions (including Taxonomy Manager's delete), and has an API
hook hook_erri_info() for other modules that use the Drupal confirm_form()
function to create their delete forms, or at least have elements either
identical to or like the ['description']['#markup'] form element and the
['actions']['submit'] button used for the delete (see
https://api.drupal.org/api/drupal/modules%21system%21system.module/funct...). If
your module's custom delete confirmation form does not have those elements
identical to those supplied by confirm_form(), you can specify equivalent
elements in hook_erri_info(). Note that the description element must be one that
permits the concatenation of text, and the submit element must be of #type
'submit'.

A module can implement hook_erri_reference_fields() to specify additional
reference fields (see erri.api.php) so that this module will enforce referential
integrity for them as well (where they are referencing either an entity or a
taxonomy term). For example, if your module implements a compound field
structure where one of the components is an entity-reference component,
hook_erri_reference_fields() will allow your module to leverage this module's
integrity checking. Such fields must be created through the field API, as this
module relies on other aspects of the Field API to do its work.

A module can implement hook_erri_reference_check() to add referring things to
the list of dependants if the module does not use the field API to store its
data, but still wants to hook into the reference checking.  In this case, your
hook is passed the target entity type, id, and bundle where there is a bundle,
and you're responsible for doing your own reference checking in the hook, and if
there are references, passing back an appropriately structured array of
references.  See erri.api.php for details.

A module can call the function erri_get_referring_entities, passing it the
specified parameters, to get a two-level array of referring entities for a
particular target, keyed on the field referencing the target, and then act
accordingly. For example:

    $fields = erri_get_referring_entities('node', $target->nid, 'customer');
    if ( !empty($fields) ) {
      foreach ( $fields as $field_name => $referring ) {
        // $referring is an array with each element an array of entity_type,
        // bundle, entity_id, etc. that all point to node $target through field
        // $field_name.
        ...
      }
    }


Installation
~~~~~~~~~~~~
Install this module like any other, and activate it.  The module will begin
working immediately.  Grant permissions as required to trusted roles if there is
a need to bypass required field constraints, or to allow certain users to make
mass changes to targets upon deleting entities.
