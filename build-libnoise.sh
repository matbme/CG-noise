#!/bin/sh

bold=$(tput bold)
normal=$(tput sgr0)

if [ -z "$(ls -A libnoise)" ]; then
    echo -e "Libnoise directory empty! You must initialize the submodule first by calling:\n
                ${bold}git submodule update --init${normal}\n"
    exit 1
fi

echo -e "${bold}Creating build directory:${normal}"
cd libnoise
mkdir -p -v build && cd build

echo -e "${bold}Compiling:${normal}"
cmake ..
make

if [ $? -ne 0 ]; then
    echo -e "${bold}Compile failed, aborting...${normal}"
    exit 1
fi

echo -e "${bold}Installing:${normal}"
sudo make install

if [ $? -eq 0 ]; then
    echo -e "${bold}Done!${normal}"
fi
