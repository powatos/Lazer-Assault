# Lazer-Assault
A simple lazer obstacle game created using Potato Engine


# todo engine
fix dograviy check
optional cammera follow
move engine wide MEMBER definitons to constructor, keep ONLY engine functions in Init/beginplay

\# Include the src directory for header files
target_include_directories(LazerAssaultGame PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/src)

MaxHealth = 100.f;
Health = MaxHealth;