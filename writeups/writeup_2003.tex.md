# 사용한 코드

```python
"""
Baekjoon Online Judge #2003
https://www.acmicpc.net/problem/2003
"""

N, M = map(int, input().split())
A = list(map(int, input().split()))
A.append(0)
lo = 0
hi = 0
running_sum = A[0]
result = 0
while lo <= hi < N:
    if running_sum < M:
        hi += 1
        running_sum += A[hi]
    elif running_sum == M:
        result += 1
        hi += 1
        running_sum += A[hi]
    elif running_sum > M:
        running_sum -= A[lo]
        lo += 1
        if hi < lo < N:
            hi = lo
            running_sum = A[lo]
print(result)
```

# 시간 복잡도
Brute-force로 답을 구하게 되면, 당연히 $O(N^2)$의 시간이 필요하게 되고, 문제의 제한 범위를 보면 이 알고리즘으로는 해결이 불가능하다는 사실을 알 수 있다.

코드를 보면 알 수 있지만, 실제로 사용한 코드의 시간 복잡도는 $O(N)$으로, 무난하게 답을 구할 수 있다.

# 투 포인터 알고리즘
이 코드에서는 투 포인터 알고리즘을 이용하여 답을 구한다. 투 포인터 알고리즘이라는 이름은 배열의 인덱스를 가리키는 변수(포인터)를 두 개 사용한다는 의미로 지어지게 되었다.

포인터의 이름을 `lo`와 `hi`라고 정하자. 초기에 `lo`와 `hi`의 값은 모두 0이고, 구간 $[lo, hi]$의 원소들의 합 `running_sum`의 값은 `A[0]`인 1이다.

배열에 담긴 값은 모두 양수이므로, `hi`를 1 더하면 당연히 `running_sum`의 값은 증가한다. 또한, `lo`를 1 증가시키면 `running_sum`의 값은 감소할 것이다.

따라서 `running_sum`과 `M`을 비교하여 각각의 경우를 다음과 같이 처리하면 된다.

조건 | 처리 |
-----|------|
`running_sum < M` | `hi` 1 증가 |
`running_sum == M` | 결과값 1 증가, `hi` 1 증가 |
`running_sum > M` | `lo` 1 증가 |

물론, `hi`와 `lo`의 값을 바꾼 뒤에는 `running_sum`의 값도 바꾸어야 할 것이다.

자, 그럼 알고리즘이 실제로 어떻게 동작하는지 보자.

$N = 7, M = 3$이고, 다음과 같은 배열을 입력받았다고 하자.

Index | 0 | 1 | 2 | 3 | 4 | 5 | 6 |
------|---|---|---|---|---|---|---|
Value | 1 | 2 | 3 | 2 | 4 | 2 | 3 |
`hi`  | ↑ |   |   |   |   |   |   |
`lo`  | ↑ |   |   |   |   |   |   |

현재 `running_sum`의 값은 1이고, $M$보다 작으므로 `hi`가 오른쪽으로 움직인다.

Index | 0 | 1 | 2 | 3 | 4 | 5 | 6 |
------|---|---|---|---|---|---|---|
Value | 1 | 2 | 3 | 2 | 4 | 2 | 3 |
`hi`  |   | ↑ |   |   |   |   |   |
`lo`  | ↑ |   |   |   |   |   |   |

이때 `running_sum`의 값은 3이므로 $M$과 같다. `hi`를 오른쪽으로 움직인다.

Index | 0 | 1 | 2 | 3 | 4 | 5 | 6 |
------|---|---|---|---|---|---|---|
Value | 1 | 2 | 3 | 2 | 4 | 2 | 3 |
`hi`  |   |   | ↑ |   |   |   |   |
`lo`  | ↑ |   |   |   |   |   |   |

`running_sum`의 값은 6, $M$보다 크므로 `lo`를 오른쪽으로 움직인다.

Index | 0 | 1 | 2 | 3 | 4 | 5 | 6 |
------|---|---|---|---|---|---|---|
Value | 1 | 2 | 3 | 2 | 4 | 2 | 3 |
`hi`  |   |   | ↑ |   |   |   |   |
`lo`  |   | ↑ |   |   |   |   |   |

`running_sum`의 값이 여전히 $M$보다 크므로 `lo`가 오른쪽으로 움직인다.

Index | 0 | 1 | 2 | 3 | 4 | 5 | 6 |
------|---|---|---|---|---|---|---|
Value | 1 | 2 | 3 | 2 | 4 | 2 | 3 |
`hi`  |   |   | ↑ |   |   |   |   |
`lo`  |   |   | ↑ |   |   |   |   |

`running_sum`이 $M$과 같다. `hi`를 오른쪽으로 움직인다.

Index | 0 | 1 | 2 | 3 | 4 | 5 | 6 |
------|---|---|---|---|---|---|---|
Value | 1 | 2 | 3 | 2 | 4 | 2 | 3 |
`hi`  |   |   |   | ↑ |   |   |   |
`lo`  |   |   | ↑ |   |   |   |   |

`running_sum`이 5, $M$보다 크다. `lo`가 오른쪽으로 움직인다.

Index | 0 | 1 | 2 | 3 | 4 | 5 | 6 |
------|---|---|---|---|---|---|---|
Value | 1 | 2 | 3 | 2 | 4 | 2 | 3 |
`hi`  |   |   |   | ↑ |   |   |   |
`lo`  |   |   |   | ↑ |   |   |   |

`running_sum`이 2, $M$보다 작다. `hi`가 오른쪽으로 움직인다.

Index | 0 | 1 | 2 | 3 | 4 | 5 | 6 |
------|---|---|---|---|---|---|---|
Value | 1 | 2 | 3 | 2 | 4 | 2 | 3 |
`hi`  |   |   |   |   | ↑ |   |   |
`lo`  |   |   |   | ↑ |   |   |   |

`running_sum`이 6, $M$보다 크므로 `lo`가 오른쪽으로 움직인다.

Index | 0 | 1 | 2 | 3 | 4 | 5 | 6 |
------|---|---|---|---|---|---|---|
Value | 1 | 2 | 3 | 2 | 4 | 2 | 3 |
`hi`  |   |   |   |   | ↑ |   |   |
`lo`  |   |   |   |   | ↑ |   |   |

`running_sum`이 4, `lo`가 오른쪽으로 움직여야 하지만 무조건 $hi \ge lo$여야 하므로 이 경우 둘 다 오른쪽으로 움직인다.

Index | 0 | 1 | 2 | 3 | 4 | 5 | 6 |
------|---|---|---|---|---|---|---|
Value | 1 | 2 | 3 | 2 | 4 | 2 | 3 |
`hi`  |   |   |   |   |   | ↑ |   |
`lo`  |   |   |   |   |   | ↑ |   |

`running_sum`이 2이다. `hi`가 오른쪽으로 움직인다.

Index | 0 | 1 | 2 | 3 | 4 | 5 | 6 |
------|---|---|---|---|---|---|---|
Value | 1 | 2 | 3 | 2 | 4 | 2 | 3 |
`hi`  |   |   |   |   |   |   | ↑ |
`lo`  |   |   |   |   |   | ↑ |   |

`running_sum`이 5, $M$보다 크기 때문에 `lo`가 오른쪽으로 움직인다.

Index | 0 | 1 | 2 | 3 | 4 | 5 | 6 |
------|---|---|---|---|---|---|---|
Value | 1 | 2 | 3 | 2 | 4 | 2 | 3 |
`hi`  |   |   |   |   |   |   | ↑ |
`lo`  |   |   |   |   |   |   | ↑ |

`running_sum`이 3, $M$과 같다. 한때 BOJ에 이렇게 맨 끝에 $M$이 있는 데이터가 존재하지 않아 데이터가 추가되고, 재채점된 적이 있다.