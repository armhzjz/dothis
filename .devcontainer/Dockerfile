# syntax=docker/dockerfile:1-labs
FROM    gcc:bullseye

# Create a non-root user
ARG     USER
ARG     UID
ARG     GID
ARG     USERNAME=${USER}
ARG     GROUPNAME=${USERNAME}
ARG     USER_UID=${UID}
ARG     USER_GID=${GID}
RUN     set -x && \
        groupadd \
                --gid ${USER_GID} \
                ${GROUPNAME} \
                && \
        useradd \
                --uid ${USER_UID} \
                --gid ${USER_GID} \
                --create-home \
                ${USERNAME} \
        && \
        :

RUN     set -x && \
        apt update && \
        apt upgrade -y && \
        apt install -y \
                sudo \
                locales \
        && \
        echo ${USERNAME} ALL=\(root\) NOPASSWD:ALL > /etc/sudoers.d/${USERNAME} && \
        chmod 0440 /etc/sudoers.d/${USERNAME} && \
        apt clean && \
        rm -fr /var/lib/apt/lists/* && \
        :
# Set the locale
RUN     sed -i '/en_US.UTF-8/s/^# //g' /etc/locale.gen && \
                locale-gen && \
                :
ENV LANG en_US.UTF-8
ENV LANGUAGE en_US:en
ENV LC_ALL en_US.UTF-8
# Switch to the non-root user
USER    ${USERNAME}
# Install stuff...
RUN     set -x && \
        sudo --preserve-env apt update && \
        sudo --preserve-env apt install -y \
                cmake \
                vim \
                less \
                gdb \
                git \
                wget \
                tar \
                bsdmainutils \
                nasm \
                bc \
                libao-dev \
                && \
        sudo --preserve-env apt clean && \
        sudo rm -fr /var/lib/apt/lists/* && \
        :
# Append aliases to .bashrc
RUN     set -x && \
                echo "alias l='ls'" >> ~/.bashrc
RUN     set -x && \
                echo "alias ll='ls -l'" >> ~/.bashrc
RUN     set -x && \
                echo "alias lll='ls -lA'" >> ~/.bashrc
# Install fuzzy finder
RUN     git clone --depth 1 https://github.com/junegunn/fzf.git ~/.fzf
RUN     cd ~/.fzf && ./install
# Install Unity
ADD     --keep-git-dir=true --chown=${USERNAME}:${GROUPNAME} https://github.com/ThrowTheSwitch/Unity.git#v2.5.2 /workspace
RUN     set -x && \
        cd /workspace && \
        cmake . && \
        make && \
        sudo make install && \
        cd / && sudo rm -fr /workspace && \
        :
