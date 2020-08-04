# CSAPP-Experiments

[![Build Status](https://travis-ci.com/Yansongsongsong/CSAPP-Experiments.svg?branch=master)](https://travis-ci.com/Yansongsongsong/CSAPP-Experiments)

This project provides the docker environments for you to take the lessons of CSAPP.

## Prerequisites

- [docker](https://docs.docker.com/docker-for-mac/install/)

## Usage

```
# take shell lab as one instance
docker run --privileged -d -p 1221:22 --name shell yansongsongsong/csapp:shelllab
# login to the envs
docker exec -it shell /bin/zsh
```

## Feature

- ZERO-config environments for you.
  There is no need to download any handout lab files. You just pull and set up the docker image, and have fun.

- zsh shell
  The environments has installed the `zsh` for you, which can give you one great interactive command-cli util.

## Hint

If you get in trouble when doing the lab, you can get some help from this [album](https://zhuanlan.zhihu.com/being-better) of articles, which is in Chinese.
