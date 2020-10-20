From now on, Utility Matrix : Content, Collaborative filtering, Latent Factor Model

# Graph Based!

## Example
- Friend Recommendation(SNS)
- query suggestion
- TV Program 추천

## What We want to Solve
- Input : Graph / Social Network
- Timestamp 생성(t0, t0', t1, t1') 후 t0부터 t0'까지의 데이터를 학습 데이터로 사용.
- t1부터 t1'까지의 데이터를 테스트로 활용.
- 목표 : 그래프에서의 두 노드의 유사도를 구하고 싶다.

## Graph Distance Method
- score(x,y) = -length

## Methods based on node neighborhoods
- Common neighbors
  - score(x,y) = 교집합의 크기
- Jaccard's coefficient
  - 하나 집합의 크기가 너무너무 커서 다른 하나를 다 포함할 경우를 고려한 것.
- Preferential Attachment
  - score(x,y) = (x의 neighbor set) * (y의 neighbor set)
- Adamic / Adar
  
  
## Methods based on the ensemble of all paths
- 

## Higher-level approaches
