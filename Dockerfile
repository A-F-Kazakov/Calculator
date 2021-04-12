from alpine as build

workdir /tmp

copy ./ /tmp

run apk update && apk add make cmake gcc g++
run cmake -S . -B build 
run cmake --build build --config Release

from alpine

run apk add libstdc++
copy --from=build /tmp/build/app/Calculator /bin

entrypoint ["Calculator"]

