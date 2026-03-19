#!/bin/sh
#Author: Jake G
#Date: 2024
#Filename: setup.sh

PKG_MNGR=""
DEBIAN=0
FBSD=0
SYSINSTALL=0
DEV_UTILS="vim tmux fzf"


install_dev_utils () {
    ICMD=""
    if [ $DEBIAN -eq 1 ]; then
        ICMD="sudo apt install"
    elif [ $FBSD -eq 1 ]; then
        ICMD="sudo pkg install"
    fi

    for util in $DEV_UTILS
    do
        ${ICMD} ${util}
    done
}


check_os () {
     if [ -f /etc/debian_version ]; then
        DEBIAN=1
    elif [ -f /etc/freebsd-update.conf ]; then
        FBSD=1
    fi  
}


remove_template_examples () {
    echo "does nothing right now"
}


install_needed_dependencies () {
    # Check the OS
    echo "checking the OS..."
    # If it's debian based then apt install
    
    # If it's freeBSD then pkg
    
    # If it's windows....you're SOL
}


create_project_symlinks () {
    # Allows the clangd LSP to find it.
    ln -s ./build/compile_commands.json ./compile_commands.json
}


build_cpputest () {
    git submodule add https://github.com/cpputest/cpputest.git
    git sumodule status
    cd ./cpputest/build
    cmake ../
    
    if [ SYSINSTALL -eq 1]; then
        make install
    else
        make
    fi
}


# The default setup stuff.
default () {
    remove_template_examples
    install_needed_dependencies
    create_project_symlinks
}

setup() {
    echo "Setting up env"
    check_os
    install_dev_utils 
}

setup
