## 1. A-Priori algorithm
### 'monotonicity' : 어떤 아이템 I가 frequent하지 않으면, I를 포함하는 어떤 pair도 frequent하지 않다.
  - Algorithm
	
    - pass 1: frequent한 singleton item 센다.(메모리 아이템 개수만큼 필요)
		
    - pass 2: pass 1에서 걸러진 item들의 쌍을 센다.(메모리 frequent singleton item^2에 비례)
		
    - pass 3: 크기가 k인 아이템셋을 이용해서 크기가 k+1인 아이템셋 후보 만든다(Ck+1)
		
    - pass 4: k+1 아이템셋 후보 중 frequent한 아이템셋을 센다.(Lk+1) - pruning 많이 된다.
    
    
## 2. PCY algorithm
### pair의 count를 세기 위한 hash table
* pass 1 algorithm

```c
for(each basket){
	for(each item in the basket){
		add 1 item's count;
	}
	for(each pair of items in the basket){	
		hash the pair to a bucket;
		add 1 to the count for the bucket;
	}
}
```

pass 1 결과 : frequent한 bucket을 알게 됨.

pass 2 : hash table을 bit-vector로 바꿔 저장한다.

* basket의 메모리 크기는 s만으로 충분

## 3. Pass의 수를 줄이는 algorithm
### 3-1. Random Sampling
#### Main memory 구성
	- 1. basket의 샘플들
	- 2. count를 위한 메모리
	
#### 주의점과 단점
	- 주의점 : minimum support를 sampling rate에 맞게 줄여줘야 함.
	- 단점
		- False Positive : pass 한번 더 돌려서 제거 가능
		- False Negative : minimum support 내리기(메모리 tradeoff, false positive문제가 있어서 해결 불가!)
		
		
### 3-2. SON
#### 전체 데이터를 k개의 chunk로 쪼갠다. 이에 맞게 minimum support 또한 s/k로 줄인다.
#### frequent한 itemset은 최소한 k개의 chunk 중 적어도 하나의 chunk에서 frequent해야 한다.
