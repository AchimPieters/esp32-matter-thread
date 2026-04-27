FROM espressif/idf:v6.0

USER root
RUN apt-get update \
    && apt-get install -y --no-install-recommends \
       bash \
       ca-certificates \
       git \
       python3-pip \
       usbutils \
    && rm -rf /var/lib/apt/lists/*

WORKDIR /workspace
CMD ["bash"]
