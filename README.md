![image](https://github.com/vishal-ahirwar/newton/assets/73791462/ad88bedd-3d72-416d-bfc7-e636fefc9de6)# C/C++ CLI Open Source Project
![Screenshot at 2022-05-07 16-12-20]
### CLI For C/C++ Project Development
# How to build newton & install on your system
### Download zip or clone newton github repo
```
git clone https://github.com/vishal-ahirwar/newton
cd newton
```

If your linux system does not have CMAKE isntall isntalled then it is must to isntall that for next step :

`Like for fedora`

```
sudo dnf install cmake 
```
`For debian based disctros `
```
sudo apt-get install cmake
```
`For arch based`
```
sudo pacman -S cmake
```

After the installation of CMAKE follow the following commands
```
cmake -S . -B build
cd build 
```


### to Compile & install on your system
```
sudo make install
```
# How to use CLI's simple functions
### to create project
```
newton create your-project-name
```
### to compile your project
```
cd your-project
newton compile
```
### to run your project
```
newton run
```
## And Congrates You have done how to use newton CLI
# Thank You for All of the project contributers and Users
```
Copyright©2022 Vishal Ahirwar and Contributers. all rights reserved.
```
