#!/bin/bash

BLUE='\033[0;34m'
CYAN='\033[0;36m'
MAGENTA='\033[0;35m'
GREEN='\033[0;32m'
RED='\033[0;31m'
NC='\033[0m'
BOLD='\033[1m'

clear

echo -e "${MAGENTA}${BOLD}"
echo "    ███████╗██╗     ██╗   ██╗██╗  ██╗     ██████╗██╗     ██╗"
echo "    ██╔════╝██║     ██║   ██║╚██╗██╔╝    ██╔════╝██║     ██║"
echo "    █████╗  ██║     ██║   ██║ ╚███╔╝     ██║     ██║     ██║"
echo "    ██╔══╝  ██║     ██║   ██║ ██╔██╗     ██║     ██║     ██║"
echo "    ██║     ███████╗╚██████╔╝██╔╝ ██╗    ╚██████╗███████╗██║"
echo "    ╚═╝     ╚══════╝ ╚═════╝ ╚═╝  ╚═╝     ╚═════╝╚══════╝╚═╝"
echo -e "${NC}"
echo -e "${CYAN}─── Personal CLI Tool Installer ───${NC}\n"

echo -e "${BLUE}[1/3]${NC} Cloning repository to /tmp..."
if [ -d "/tmp/flux-cli" ]; then
    rm -rf /tmp/flux-cli
fi

git clone https://github.com/XH1mura/flux-cli.git /tmp/flux-cli &> /dev/null

if [ $? -eq 0 ]; then
    echo -e "      ${GREEN}✔ Repository cloned successfully${NC}"
else
    echo -e "      ${RED}✘ Failed to clone repository${NC}"
    exit 1
fi

echo -e "${BLUE}[2/3]${NC} Preparing installation script..."
cd /tmp/flux-cli
chmod +x install.sh

echo -e "${BLUE}[3/3]${NC} Launching main installer...\n"
echo -e "${MAGENTA}------------------------------------------${NC}"

exec ./install.sh
