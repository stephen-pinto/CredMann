#pragma once

#ifdef _DEBUG
#define _PRINT(str) std::cout << str << std::endl;
#else
#define _PRINT(str) 
#endif