#!/bin/sh
# Author: Jake Goodwin
# Date: 2025
# Filename: otto.sh

CMAKE_VERBOSE="ON"
TEMPLATE_FILES=".template_files"
MODULE_DIR="${TEMPLATE_FILES}/modules"
TEST_MODULE_DIR="${TEMPLATE_FILES}/test_module"
PROJECT_NAME="comic_tagger"

generate_tags_file () {
    echo "generate_tags_file()"
    # Saving current directory
    #CUR_DIR=$(pwd)

    uctags --recurse=yes \
        --languages=C,C++,Asm \
        --extras=+q \
        --fields=+iaS \
        --exclude=extern \
        --exclude=build \
        --exclude=.git \
        --exclude=.template_files \
        ./
}

format_source_code () {
    #Get a list of all C files
    source_c_files=$(find ./src ./tests/shared -name '*.c')
    for f in $source_c_files; do
        clang-format -i -style=file $f
    done

    #Get a list of all H files
    source_h_files=$(find ./src ./tests -name '*.h')
    for f in $source_h_files; do
        clang-format -i -style=file $f
    done

    #Get a list of all Cpp files.
    source_cpp_files=$(find ./src ./tests/shared -name '*.cpp')
    for f in $source_cpp_files; do
        clang-format -i -style=file $f
    done

    echo "Applying Formating standard!"
}

add_compile_commands () {
    if [ -f ./compile_commands.json ]; then
        echo "compile_commands.json already exists!"
    else
        echo "Creating new symlink for compile commands!"
        ln -s ./build/compile_commands.json ./compile_commands.json
    fi
}

clear_cmake_cache () {
    cd ./build
    rm -rf CMakeCache.txt CMakeFiles/
}


does_module_exist () {
    local basename="$1"
    
    if [ -d "src/${basename}" ]; then
        echo "1"
    else
        echo "0"
    fi
}

does_mock_exist () {
    local basename="$1"
    
    if [ -d "mocks/${basename}" ]; then
        echo "1"
    else
        echo "0"
    fi
}


add_module_to_cmakes () {
    local basename="$1"
    echo "add_module_to_cmakes()"    
    echo "add_subdirectory(${basename})" >> ./src/CMakeLists.txt
    
    # Tests cmake file needs to be edited in place.
    sed -i '' -e "s|# TEST_DIRS.*$|# TEST_DIRS\nadd_subdirectory(${basename})|" ./tests/CMakeLists.txt
    sed -i '' -e "s|# TEST_LINKS.*$|# TEST_LINKS\ntest_${basename}|" ./tests/CMakeLists.txt
}

remove_module_from_cmakes () {
    local basename="$1"

    sed -i'' "s/^.*add_subdirectory(${basename}).*$//g" ./src/CMakeLists.txt
    sed -i'' "s/^.*add_subdirectory(${basename}).*$//g" ./tests/CMakeLists.txt
    sed -i'' "s/^.*test_${basename}.*$//g" ./tests/CMakeLists.txt
}

git_add_module () {

    local basename="$1"
    
    read -p "Auto add to git?(y/n):" CHOICE
    if [ "${CHOICE}" = "n" ]; then
        echo "not being added!"
        return 0
    fi
    
    modsrc_dir="./src/${basename}"
    modtest_dir="./tests/${basename}"

    # Now we add the new files to the git tracked files
    git add ${modsrc_dir}/*
    git add ${modsrc_dir}
    git add ${modtest_dir}/*
    git add ${modtest_dir}
    git add ./src/CMakeLists.txt
    git add ./tests/CMakeLists.txt
}


git_remove_module () {
    local basename="$1"
    
    read -p "Auto del from git?(y/n):" CHOICE
    if [ "${CHOICE}" -eq "n" ]; then
        echo "not being removed!"
        return 0
    fi

    modsrc_dir="./src/${basename}"
    modtest_dir="./tests/${basename}"

    # Now we add the new files to the git tracked files
    git rm -r ${modsrc_dir}/*
    git rm -r ${modsrc_dir}
    git rm -r ${modtest_dir}/*
    git rm -r ${modtest_dir}
    git rm -r ./src/CMakeLists.txt
    git rm -r ./tests/CMakeLists.txt
}


add_mock_module () {
    read -p "Enter the name of the module:" modname
    result=$(does_mock_exist "$modname")

    if [ "${result}"  -eq "1" ]; then
        echo "Module already exists!"
        echo "Exiting without changing anything"
        exit
    fi

    # modname_cap=$(echo $modname | sed 's/[a-z]/\U&/g')
    modname_cap="${modname}"
    modsrc_dir="./mocks/${modname}"
    modtest_dir="./tests/${modname}"

    echo "creating: ${modsrc_dir}, ${modtest_dir}"
    mkdir $modsrc_dir
    mkdir $modtest_dir
    
    #copy the template files.
    echo "copying & customizing template files..."

    echo "Creating src files..."    
    sed  "s/module_name/${modname}/g" "${MODULE_DIR}/module_name.c" >  ${modsrc_dir}/${modname}.c
    sed -i''  "3s/todays_date/$(date +%Y)/" "${modsrc_dir}/${modname}.c"

    sed "s/module_name/${modname_cap}/g" "${MODULE_DIR}/module_name.h" > ${modsrc_dir}/${modname}.h  
    sed -i''  "3s/todays_date/$(date +%Y)/" "${modsrc_dir}/${modname}.h"

    sed  "s/module_name/${modname}/g" "${MODULE_DIR}/CMakeLists.txt" > ${modsrc_dir}/CMakeLists.txt

    echo "Creating test files..."    
    sed  "s/module_name/${modname}/g" "${MODULE_DIR}/test_module_name.cpp" > ${modtest_dir}/test_${modname}.cpp
    sed  "s/module_name/${modname}/g" "$MODULE_DIR/TestCMakeLists.txt" > ${modtest_dir}/CMakeLists.txt
   
    # Add the module to the cmake lists files.
    add_module_to_cmakes "${modname}" 

    echo "Resulting files/dirs:"
    tree -L 2 $modsrc_dir
    tree -L 2 $modtest_dir
    
    # Now we add the new files to the git tracked files
    git_add_module "${modname}" 

}

add_new_module () {
    read -p "Enter the name of the module:" modname
   
    result=$(does_module_exist "$modname")

    if [ "${result}"  -eq "1" ]; then
        echo "Module already exists!"
        echo "Exiting without changing anything"
        exit
    fi

    #modname_cap=$(echo $modname | sed 's/[a-z]/\U&/g')
    modname_cap="${modname}"
    modsrc_dir="./src/${modname}"
    modtest_dir="./tests/${modname}"

    echo "modname_cap: ${modname_cap}"
    echo "modname: ${modname}"

    echo "creating: ${modsrc_dir}, ${modtest_dir}"
    mkdir $modsrc_dir
    mkdir $modtest_dir
    
    #copy the template files.
    echo "copying & customizing template files..."
   
 
    echo "Creating src files..."    
    sed -e "s/module_name/${modname}/g" $MODULE_DIR/module_name.c >  $modsrc_dir/${modname}.c
    sed -i '' -e "3s/todays_date/$(date +%Y)/" $modsrc_dir/${modname}.c

    sed  -e "s/module_name/${modname_cap}/g" $MODULE_DIR/module_name.h > $modsrc_dir/${modname}.h  
    sed -i '' -e "5s/todays_date/$(date +%Y)/" $modsrc_dir/${modname}.h

    sed -e "s/module_name/${modname}/" ${MODULE_DIR}/CMakeLists.txt > $modsrc_dir/CMakeLists.txt


    echo "Creating test files..."    
    sed -e "s/module_name/${modname}/g" ${TEST_MODULE_DIR}/test_module_name.cpp > ${modtest_dir}/test_${modname}.cpp
    sed -e "s/module_name/${modname}/g" ${TEST_MODULE_DIR}/CMakeLists.txt > ${modtest_dir}/CMakeLists.txt
    cp -r ${TEST_MODULE_DIR}/mocks ${modtest_dir}/
    cp -r ${TEST_MODULE_DIR}/fakes ${modtest_dir}/
    cp -r ${TEST_MODULE_DIR}/stubs ${modtest_dir}/

    # Add the module to the cmake lists files.
    add_module_to_cmakes "${modname}" 

    echo "Resulting files/dirs:"
    tree -L 2 $modsrc_dir
    tree -L 2 $modtest_dir
    
    # Now we add the new files to the git tracked files
    git_add_module "${modname}" 


}


del_module () {
    read -p "Enter the name of the module:" modname
    
    rm -r ./tests/${modname}
    rm -r ./src/${modname} 
    remove_module_from_cmakes "${modname}"
}

cross_compile () {
    echo "ERROR: Currently no toolchain / target!"
}

build_release() {
    clear_cmake_cache 
    cmake -DCMAKE_VERBOSE_MAKEFILE=${CMAKE_VERBOSE} ../ 
    make 
}

build_main () {
    clear_cmake_cache
    cmake -DCMAKE_VERBOSE_MAKEFILE=${CMAKE_VERBOSE} ../
    make main
}

run_c_tests () {
    generate_tags_file
    format_source_code 
    clear_cmake_cache
    cmake -DUNIT_TESTING=ON  -DCMAKE_VERBOSE_MAKEFILE=${CMAKE_VERBOSE} ../

    if make AllTests; then
        echo "Running: AllTests -c -v"
        ./tests/AllTests -v -c
    else
        echo "Failed to build AllTests."
        echo "Press anykey to exit:"
        read input 
    fi

    read -p "Press anykey to continue:" input

    if make MockedMemTests; then
        echo "Running: MockedMemTests -c -v"
        ./tests/MockedMemTests -v -c
    else
        echo "Failed to build AllTests."
        echo "Press anykey to exit:"
        read input 
    fi

    #read -p "Press anykey to continue:" input

}

print_menu () {
    echo "BUILD MENU:"
    echo "0. Add Mock Module"
    echo "1. Run Tests"
    echo "2. Build Project"
    echo "3. Build for release"
    echo "4. blank"
    echo "5. Add new module to project"
    echo "6. Delete module from project"
    echo "7. Exit"
}


main() {
    add_compile_commands 
    valid_choice=false
    
    while [ "$valid_choice" != true ]; do
        print_menu
        read -p "Enter your choice: " choice

        case $choice in
            0)
                echo "You selected Option 0"
                valid_choice=true
                add_mock_module 
                ;;
            1)
                echo "You selected Option 1"
                valid_choice=true
                run_c_tests
                ;;
            2)
                echo "You selected Option 2"
                echo "Not yet implimented" 
                valid_choice=true
                ;;
            3)
                echo "You selected Option 3"
                valid_choice=true
                echo "Not yet implimented" 
                ;;
            4)
                echo "You selected Option 4"
                valid_choice=true
                echo "Not yet implimented" 
                ;;
            5)
                echo "You selected Option 5"
                valid_choice=true
                add_new_module 
                ;;
            6)
                echo "You selected Option 6"
                valid_choice=true
                del_module 
                ;;
            7)
                echo "Exiting..."
                exit 0
                ;;
            *)
                echo "Invalid choice. Please select a valid option."
                ;;
        esac
    done
}

main
