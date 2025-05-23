cmake_minimum_required(VERSION 3.10)
project(DedsecTool VERSION 1.0 LANGUAGES CXX)

# Spécifier la norme C++17
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Configuration des répertoires de sortie
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)

# Créer le répertoire de sortie s'il n'existe pas
file(MAKE_DIRECTORY ${CMAKE_RUNTIME_OUTPUT_DIRECTORY})
file(MAKE_DIRECTORY ${CMAKE_LIBRARY_OUTPUT_DIRECTORY})
file(MAKE_DIRECTORY ${CMAKE_ARCHIVE_OUTPUT_DIRECTORY})

# Inclure les répertoires d'en-têtes
include_directories(${CMAKE_SOURCE_DIR}/src)
include_directories(${CMAKE_SOURCE_DIR}/src/include)
include_directories(${CMAKE_SOURCE_DIR}/src/commands)
include_directories(${CMAKE_SOURCE_DIR}/src/utils)

# Options de compilation
if (WIN32)
    add_compile_definitions(OS_WINDOWS _WIN32_WINNT=0x0601)
    if(MSVC)
        add_compile_options(/W4 /WX)
        # Activer la compilation multithread
        add_compile_options(/MP)
        # Activer les optimisations de vitesse
        add_compile_options(/O2)
        # Lier statiquement la bibliothèque d'exécution C++
        set(CMAKE_MSVC_RUNTIME_LIBRARY "MultiThreaded$<$<CONFIG:Debug>:Debug>")
    endif()
endif()

# Fichiers source
set(SOURCES
    src/main.cpp
    src/dedsec.cpp
)

# Fichiers d'en-tête
set(HEADERS
    src/include/dedsec.hpp
    src/commands/commands.hpp
    src/utils/animation.hpp
    src/config.h
)

# Créer l'exécutable
add_executable(${PROJECT_NAME} ${SOURCES} ${HEADERS})
    
    # Lier les bibliothèques Windows nécessaires
    set(WIN32_LIBS advapi32 shell32)
    
    # Configuration spécifique à Windows
    add_definitions(-D_WIN32_WINNT=0x0601 -DWIN32_LEAN_AND_MEAN -DNOMINMAX)
    
    # Désactiver les avertissements spécifiques
    if(MSVC)
        add_compile_options(/wd4996)  # Désactive l'avertissement concernant les fonctions dépréciées
        add_compile_options(/wd4251)  # Désactive l'avertissement de visibilité de la classe DLL
    endif()
    
    # Activer les fonctionnalités expérimentales du système de fichiers
    add_compile_definitions(_SILENCE_EXPERIMENTAL_FILESYSTEM_DEPRECATION_WARNING)
    
    # Ajouter des chemins d'inclusion supplémentaires pour Windows
    include_directories(${CMAKE_SOURCE_DIR}/include)
    
    # Configuration Release
    set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} /MT")
    set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} /MTd")
    
    # Configuration pour la compilation multithread
    set(THREADS_PREFER_PTHREAD_FLAG ON)
    find_package(Threads REQUIRED)
    
    # Désactiver les avertissements de conversion de taille pour MSVC
    if(MSVC)
        add_compile_options(/wd4267)  # Conversion de 'size_t' en 'type', perte possible de données
        add_compile_options(/wd4244)  # Conversion de 'type1' en 'type2', perte possible de données
    endif()
    
    # Activer les avertissements de niveau 4
    if(MSVC)
        add_compile_options(/W4)
    else()
        add_compile_options(-Wall -Wextra -pedantic)
    endif()
    
    # Traiter les avertissements comme des erreurs en mode Release
    if(MSVC)
        add_compile_options($<$<CONFIG:RELEASE>:/WX>)
    else()
        add_compile_options($<$<CONFIG:RELEASE>:-Werror>)
    endif()
    
    # Options de débogage
    if(MSVC)
        add_compile_options($<$<CONFIG:DEBUG>:/Zi /Od>)
        set(CMAKE_EXE_LINKER_FLAGS_DEBUG "/DEBUG /INCREMENTAL:NO")
    else()
        add_compile_options($<$<CONFIG:DEBUG>:-g -O0>)
    endif()
    
    # Options de version
    set(PROJECT_DESCRIPTION "Dedsec - Outil de développement et d'analyse système")
    set(PROJECT_HOMEPAGE_URL "https://github.com/darkiiuseai/dedsec-tool")
    
    # Configuration des propriétés du projet
    set_property(DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR} PROPERTY VS_STARTUP_PROJECT ${PROJECT_NAME})
    
    # Activer la prise en charge des modules C++20 si disponible
    if(CMAKE_CXX_COMPILER_ID MATCHES "MSVC")
        if(CMAKE_CXX_COMPILER_VERSION VERSION_GREATER_EQUAL "19.28")
            set(CMAKE_CXX_STANDARD 20)
            set(CMAKE_CXX_EXTENSIONS OFF)
            add_compile_definitions(_SILENCE_ALL_CXX20_DEPRECATION_WARNINGS)
        endif()
    endif()
    
    # Configuration pour les tests unitaires
    option(ENABLE_TESTS "Build tests" OFF)
    if(ENABLE_TESTS)
        enable_testing()
        add_subdirectory(tests)
    endif()
    
    # Installation
    install(TARGETS ${PROJECT_NAME}
            RUNTIME DESTINATION bin
            LIBRARY DESTINATION lib
            ARCHIVE DESTINATION lib/static)
    
    # Inclure les fichiers d'en-tête dans l'installation
    install(DIRECTORY include/ DESTINATION include)
    
    # Package configuration
    include(CMakePackageConfigHelpers)
    write_basic_package_version_file(
        ${CMAKE_CURRENT_BINARY_DIR}/${PROJECT_NAME}ConfigVersion.cmake
        VERSION ${PROJECT_VERSION}
        COMPATIBILITY AnyNewerVersion
    )
    
    # Installation des fichiers de configuration du package
    install(FILES
        ${CMAKE_CURRENT_BINARY_DIR}/${PROJECT_NAME}ConfigVersion.cmake
        DESTINATION lib/cmake/${PROJECT_NAME}
    )
    
    # Configuration de CPack
    set(CPACK_PACKAGE_NAME ${PROJECT_NAME})
    set(CPACK_PACKAGE_VERSION ${PROJECT_VERSION})
    set(CPACK_PACKAGE_DESCRIPTION_SUMMARY ${PROJECT_DESCRIPTION})
    set(CPACK_PACKAGE_VENDOR "Dedsec Team")
    set(CPACK_PACKAGE_CONTACT "contact@dedsec.tools")
    set(CPACK_RESOURCE_FILE_LICENSE "${CMAKE_CURRENT_SOURCE_DIR}/LICENSE")
    set(CPACK_PACKAGE_INSTALL_DIRECTORY ${PROJECT_NAME})
    
    if(WIN32 AND NOT UNIX)
        set(CPACK_GENERATOR "ZIP;NSIS")
        set(CPACK_NSIS_DISPLAY_NAME "Dedsec Tool")
        set(CPACK_NSIS_PACKAGE_NAME "Dedsec Tool")
        set(CPACK_NSIS_UNINSTALL_NAME "Uninstall")
        set(CPACK_NSIS_HELP_LINK ${PROJECT_HOMEPAGE_URL})
        set(CPACK_NSIS_URL_INFO_ABOUT ${PROJECT_HOMEPAGE_URL})
        set(CPACK_NSIS_CONTACT ${CPACK_PACKAGE_CONTACT})
        set(CPACK_NSIS_MODIFY_PATH ON)
    else()
        set(CPACK_GENERATOR "TGZ")
    endif()
    
    include(CPack)
else()
    add_compile_options(-Wall -Wextra -Wpedantic -Werror)
endif()

# Fichiers sources
file(GLOB_RECURSE SOURCES 
    "src/*.cpp"
    "src/commands/*.cpp"
    "src/utils/*.cpp"
)

# Exécutable principal
add_executable(dedsec ${SOURCES})

# Options de liaison
if(UNIX AND NOT APPLE)
    target_link_libraries(dedsec PRIVATE stdc++fs)
endif()

# Installation
install(TARGETS dedsec DESTINATION bin)
