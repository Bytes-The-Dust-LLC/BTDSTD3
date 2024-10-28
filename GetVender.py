#downloads the vender packages needed for compiling.
#GitPython is required to be installed via Pip

from git import Repo
import os
import subprocess

#clones a repo into vender
def GitClone(URL, name, branch = "master"):
     #checks if Vender folder exists
    if not os.path.exists("Venders"):
        os.mkdir("Venders")

    #if it already exists, don't clone it
    if not os.path.exists("Venders/" + name):
        print("Cloning " + name + ".....")
        Repo.clone_from(URL, "Venders/" + name, branch = branch)
        print("Done cloning " + name)

GitClone("https://github.com/fmtlib/fmt.git", "FMT")
GitClone("https://github.com/g-truc/glm.git", "GLM")
GitClone("https://github.com/nothings/stb.git", "STB")

GitClone("https://github.com/GPUOpen-LibrariesAndSDKs/VulkanMemoryAllocator.git", "VMA")
GitClone("https://github.com/charles-lunarg/vk-bootstrap.git", "VKBootstrap", "main")
GitClone("https://github.com/zeux/volk.git", "Volk")

GitClone("https://github.com/libsdl-org/SDL.git", "SDL", "SDL2")

#builds each of the SDL configs
#subprocess.run(["cmake", "-S", "Venders/SDL", "-B", "Venders/SDL/Build"],
#    shell=True)
#subprocess.run(["msbuild", "Venders/SDL/Build/SDL2.sln", "-maxCpuCount:4", "/property:Configuration=Release"],
#    shell=True)
#subprocess.run(["msbuild", "Venders/SDL/Build/SDL2.sln", "-maxCpuCount:4", "/property:Configuration=MinSizeRel"],
#    shell=True)
#subprocess.run(["msbuild", "Venders/SDL/Build/SDL2.sln", "-maxCpuCount:4", "/property:Configuration=RelWithDebInfo"],
#    shell=True)