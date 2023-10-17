include(FetchContent)

set(CALLME_ASMJIT_GIT_REPOSITORY "git@github.com:asmjit/asmjit.git" CACHE STRING "asmjit git repository.")
set(CALLME_ASMJIT_GIT_TAG "master" CACHE STRING "asmjit git repository tag.")

function(
    ImportAsmJit
)
    FetchContent_Declare(
        asmjit
        GIT_REPOSITORY ${CALLME_ASMJIT_GIT_REPOSITORY}
        GIT_TAG ${CALLME_ASMJIT_GIT_TAG}
        GIT_SHALLOW ON
        GIT_PROGRESS ON
    )
    FetchContent_MakeAvailable(asmjit)
    message(STATUS "[callme] import asmjit.")
endfunction()
