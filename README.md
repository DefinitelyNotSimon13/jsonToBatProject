

[Doxygen Documentation](https://definitelynotsimon13.github.io/jsonToBatProject/)

[Sonar Cloud](https://sonarcloud.io/dashboard?id=DefinitelyNotSimon13_jsonToBatProject&branch=main)

# README

<details>
<summary>Current workflows:</summary>
    
- build
    - build and test the application on:
        - windows with cl
        - ubunut with g++
        - ubuntu with clang++
- buildWithPrecompiled
    - Same as build but with the precompiled libraries
- CodeQl
    - Code security
- Doxygen Action
    - Generate Doxygen documentation
    - Deploys generated documentation to gh-pages
- Microsoft C++ Code Analysis
- pages-build-deployment
- SonarCloud
    - Static code analysis
_For Scanning Alerts -> Security_

</details>

<details>
<summary>Regarding coding style (?):</summary>
    
- no classes in global namespace
- no "using NAMESPACE"
- 4 space indenting
- ?
_setup astyle options?_

</details>

<details>
<summary>Git (?):</summary>
    
- no direct commits onto main (only via pull-requests)
- 
</details>

<details>
<summary>Libraries</summary>
    
- jsoncpp
- Easyloggingpp
- Catch2

Libraries can be found in ./lib. They are subprojects and will be compiled when building the project for the first time. Alternatevly compiled versions can be found at ./lib/compiled.
As is, this approach works on linux (gcc, clang) and Windows (Mingw). As steps found in the tutorial (checking for compiler in cmake) are not necessary.

## Precompiled
By setting the flag ```-DPRECOMPILED=ON``` when initialising the cmake project, the precompiled versions of the libraries will be used.
***This does currently not work under windows***

</details>




