FROM debian:latest

RUN apt update -y && export DEBIAN_FRONTEND=noninteractive && apt install -y \
    build-essential \
    tcsh \
    vim \
    vim-scripts \
    flex \
    bison \
    python3 \
    python3-crontab \
    valgrind \
    && rm -Rf /var/lib/apt/lists/*

ENTRYPOINT ["/app/docker-entrypoint.sh"]
CMD ["/app/scripts/container/start_app.csh"]
