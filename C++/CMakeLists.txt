cmake_minimum_required(VERSION 3.10)
project(CryptoAlgorithms LANGUAGES CXX)

# Настройка стандарта C++ (рекомендую 17 или новее)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Включить debug-символы по умолчанию в Debug-сборке
if(CMAKE_BUILD_TYPE STREQUAL "Debug")
    add_compile_options(-g)
endif()

# Ручной поиск библиотек GMP (более надежный способ)
find_path(GMP_INCLUDE_DIR gmp.h
    PATHS /usr/include /usr/local/include
    REQUIRED
)
find_library(GMP_LIBRARY NAMES gmp
    PATHS /usr/lib /usr/local/lib
    REQUIRED
)
find_library(GMPXX_LIBRARY NAMES gmpxx
    PATHS /usr/lib /usr/local/lib
    REQUIRED
)

# Директории с исходными файлами
include_directories(include ${GMP_INCLUDE_DIR})
set(SOURCE_DIR src)

set(SOURCES
    ${SOURCE_DIR}/main.cpp
    ${SOURCE_DIR}/utils/math_utils.cpp
    ${SOURCE_DIR}/utils/menu_utils.cpp
    ${SOURCE_DIR}/algorithms/mod_inverse1.cpp
    ${SOURCE_DIR}/algorithms/mod_inverse2.cpp
    ${SOURCE_DIR}/algorithms/modexp.cpp
    ${SOURCE_DIR}/algorithms/shamir.cpp
    ${SOURCE_DIR}/algorithms/solveDiophantine.cpp
    ${SOURCE_DIR}/algorithms/attackSimulations.cpp
)

# Создание исполняемого файла
add_executable(${PROJECT_NAME} ${SOURCES})

# Подключение библиотек
target_link_libraries(${PROJECT_NAME} PRIVATE
    ${GMP_LIBRARY}
    ${GMPXX_LIBRARY}
)

# Установка выходного каталога для исполняемого файла
set(EXECUTABLE_OUTPUT_PATH ${CMAKE_BINARY_DIR}/bin)

# Копирование тестовых данных в build directory (опционально)
file(GLOB TEST_DATA_FILES "data/*.txt")
foreach(data_file ${TEST_DATA_FILES})
    configure_file(${data_file} ${CMAKE_BINARY_DIR}/data COPYONLY)
endforeach()

# Для Windows: скопировать DLL, если используются (опционально)
if(WIN32)
    add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_if_different
        "$<TARGET_RUNTIME_DLLS:${PROJECT_NAME}>"
        "$<TARGET_FILE_DIR:${PROJECT_NAME}>"
        COMMAND_EXPAND_LISTS
    )
endif()

# Вывод информации о найденных библиотеках
message(STATUS "GMP include dir: ${GMP_INCLUDE_DIR}")
message(STATUS "GMP library: ${GMP_LIBRARY}")
message(STATUS "GMPXX library: ${GMPXX_LIBRARY}")
