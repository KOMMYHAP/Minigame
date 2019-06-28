set_property(GLOBAL PROPERTY USE_FOLDERS ON)

function(project_group target group)
    set_target_properties(${target} PROPERTIES FOLDER ${group})
endfunction(project_group)