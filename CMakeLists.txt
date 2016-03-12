if (NOT VARMNG_BUILD_MODE)
    set (VARMNG_BUILD_MODE STATIC)
endif ()

include(pile_support)
pileInclude (VarMng)
varmngInit(${VARMNG_BUILD_MODE})
