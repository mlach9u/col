
# Collection of libraries.
---
<https://www.github.com/mlach9u>

## 라이선스
이 프로젝트의 모든 코드는 직접 작성하였으며, Public Domain에 속합니다.

## 기반 구조

모든 COL 프로젝트는 C++ Template 문법을 기반으로 작성합니다.

모든 COL 프로젝트는 아래와 같은 이유로 기본적으로 전역 namespace에 정의됩니다.

1. 모든 프로젝트는 규모가 작습니다.
2. 모든 프로젝트는 표준 라이브러리만 포함합니다.
3. 다른 namespace로의 포함이 간단해야 합니다.

모든 COL 프로젝트는 적어도 `inclusion_(name).h` 파일과 `(name).h` 파일을 가지고 있으며 이 파일들은 아래 내용을 포함합니다. 필요한 경우 추가 파일을 생성할 수 있습니다.

1. `inclusion_(name).h` 파일에는 표준 라이브러리가 포함됩니다.
2. `(name).h` 파일에는 프로젝트의 실제 정의가 포함됩니다.

특정 COL 프로젝트를 다른 namespace로 포함하고자 한다면 아래의 내용대로 namespace를 변경해야 합니다.

1. `inclusion_(name).h` 파일을 전역 namespace에 포함합니다.
2. `(name).h` 파일을 사용할 namespace에 포함합니다.

예를 들면, 아래와 같습니다.

```cpp
#include "src\\stringt\\inclusion_stringt.h"
namespace something
{
#include "src\\stringt\\stringt.h"
}
```
