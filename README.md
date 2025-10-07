## MGC or simply Mini Git CLI
MGC is an attempt at recreating git functionality with the purpose of deeper understanding of git internals as well as learning how complex systems are created and implemented.

* MGC supports the following commands:
```bash
# Initialized empty repository in the current folder
mgc init

# Adds/Stages a single file or the whole folder if passed . as an option
mgc add <filename || .>

# Commits staged files
mgc commit "message"

# Shows current repository status: Staged files and working directory
mgc status

# Logs the Repository logs (created, commited, etc)
mgc log

# Dummy function with the idea of later adding git push/pull/clone functionality using curl
# For now it simply calls the follwing url: http://localhost:3000/hello for testing purposes
mgc test 
```

## Instalation

* To install the CLI:

- Download the Zip / Clone the repository.
- GLOBAL USAGE: To use globally add the /bin folder to ENV Path variables. Use from anywhere using Terminal/Command Line -> Should not interfere with other Path variables.
If any issues arise, feel free to remove the Path variable from ENV config.
- LOCAL USAGE: For one time use open a terminal from the /bin folder and run ```mgc.exe <command> <option>```   Works directly in /bin folder which can be an unwanted / useless effect.
- If any changes to the files are made rebuild the exe using build.bat

* Recommended usage: Global

* IMPORTANT
* libcurl-x64.dll needs to be present in the root directory of the project for build.bat to work.
Build.bat compiles using g++ and links neccessary libraries, one of which is libcurl.dll, which it copies to /bin for the mgc.exe file to link to during runtime.
Had issues statically linking to curl.

## Under the hood

* Project structure is as follows:
```bash
├── include
├── lib
├── bin
├── src
├── main.cpp
├── .gitignore
├── .mgc-ignore
└── build.bat
```

- /include       #  Contains all of the header files for the application
- /lib           # Contains all of the libraries needed to compile // for curl + openssl
- /src           # Includes the implementation of applications internal header files
- main.cpp       # Main entry point of the application
- .mgc-ignore    # Similar to .gitignore -> list all files you wish to ignore from staging/commiting
- build.bat      # Build script to run if any changes are made to the codebase

## Implementation

### App uses std::filesystem to handle file manipulations.

### repo.cpp -> Responsible for initialization of the repository. It checks if a repository already exists in the current folder and if it doesn't it creates one.

### staging.cpp -> Contains function for checking ignored files, as well as adding / staging files.

* If option . is passed as a parameter it recursively traverses the folder adding and hashing each folder and file it finds. (Excludes .mgc itself, .mgc-ignore and files/folders specified in .mgc-ignore)
* Files are hashed using <openssl/evp> using sha1 algorithm (<openssl/sha1> is depreciated since openssl v3.0+)
* File hashes are used for tracking changes between files, if hash remains the same -> file is unchanged and ignored.
* Else stage file again + assign new hash.
* Staged/Added files are added to the .mgc/staging folder

### hash.cpp + hash_utils.cpp -> helper functions that do the actual hashing.
### Hashing uses evp.h instead of sha.h due to openssl depreciation.

### commit.cpp -> Responsible for commiting staged files. If a file is unchanged (checked via file hash) it is ignored and only changed files are commited.
* During commit a message for that commit is added as a string format i.e ``` mgc commit "commit message" ```
* Staged files are moved to commit folder and Staging folder is cleaned, ready for new files to be staged.

### utils.cpp -> Helper functions such as showHelp definition and getting current local time to use for file time stamps. 
* Useful for logs and commit history.

###
