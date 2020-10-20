## Frequent itemset mining 동기
	연관 모델: Market-Basket Model
  
	목표
		- 1. Association rule(if-then rule) 찾기 - 빈발성도 중요
		- 2. 특정 바스켓에 자주 빈발하게 나타나는 아이템 찾기

## Frequent itemset이란?
	- Support : Itemset I에 있는 모든 아이템을 포함하는 바스켓의 개수
	
	- Frequent Itemset : Support > s
  
	* Association Rule
	- Confidence(I->J) : I를 샀다면 J를 살 확률(I&J포함/I포함)
	
	- Interest(I->J) = Confidence(I->J) - P(J)
	
		- Interest 높을 때 : I를 사면 J를 살 확률이 높고 이건 J자체가 높아서가 아님
		
    - Interest 낮을 때 :
		
			- P(J) 높은 경우 J자체는 많이 팔리는데 왠지 I를 사면 J를 안삼(==I 자체가 안팔림)

      - 그러나 Confidence가 높은 경우, 흥미로운 규칙은 아님
			
	- 우리는 Confidence > c, P(==support) > s 인 것을 원함
  
  #### Algorithm
  - 1. Frequent Itemset를 찾는다
  
  - 2. Confidence 경계 넘는 것 찾는다
    
## 문제점
  - 데이터는 DB가 아닌, 파일에 저장(디스크에 저장) - 디스크 I/O 중요
  
  - Itemset의 길이(n)가 길 경우 부분집합의 개수가 (2^n)-1이 됨 - 메모리에 다 저장되지 못함.
  
  - 그래서 메모리에는 현재 세고 있는 것만 올리자.(메모리를 효율적으로 쓰자)
  
  - 해결 : 의미있는 아이템셋에 초점을 맞추자
  
    - Maximum Frequent Itemset
    
      - 특정 itemset보다 빈발한 itemset이 없는 itemset
      
    - Closed Frequent Itemset
    
      - Superset인데 같은 support를 갖는 Frequent한 set이 없을 경우
      
  - 해결 : A-priori(가지치기)
