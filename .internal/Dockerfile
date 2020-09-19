# Commands
# sudo docker build -t aloknigam247/cygnus -f .docker/Dockerfile .
# sudo docker push aloknigam247/cygnus
FROM gcc:9.2.0 # Move to gcc 10

RUN apt-get update
RUN apt-get upgrade -y

RUN apt-get install -y software-properties-common
RUN apt-add-repository "deb http://apt.llvm.org/bionic/ llvm-toolchain-bionic-9 main"
RUN wget -O - https://apt.llvm.org/llvm-snapshot.gpg.key | apt-key add -
RUN apt-get update

RUN apt-get install -y clang-tidy
RUN apt-get install -y cppcheck
RUN apt-get install -y doxygen
RUN apt-get install -y flex
RUN apt-get install -y g++-7
RUN apt-get install -y graphviz
RUN apt-get install -y lcov
RUN apt-get install -y python3.7
RUN apt-get install -y valgrind
