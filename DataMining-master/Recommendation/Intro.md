## Motivation
- too much information
- Netflix, Amazon, News
- Offline
  - 개인의 취향을 고려하지 못함. 유명한 상품만(공간한정 때문)
- Online
  - 덜 유명한 제품 추천 가능, 개인화 가능
  
## Formal Model
- X : set of users
- S : set of items
- Utility Matrix U(X,S)-> *R
- R을 잘 예측해야!

## Steps
> rating 모으고 -> 예측 후 -> 평가
- 1. Gather known ratings
  - Explicit rating(*평점이 매겨진 정보*만 활용해야!)
  - Implicit rating(행동 기반 : 클릭횟수, 방문 웹사이트)
  
- 2. Predict Unknown Ratings from the known Ratings
  - Content-based 기법
  - Collaborative Filtering 기법
  - Latent Factor 기법
  
- 3. Evaluate Predictions

## Problem
- Coldstart
  - new items
  - new users
- Data Sparsity Problem(Sparse Matrix)

  
### Content-Based Recommendations
> Main Idea : 사용자가 기존에 재미있게 본 것과 유사한 콘텐츠를 추천한다.
> Approach : 사용자의 기존 item profile을 기반으로 User Profile을 만들고, user profile과 비슷한 아이템을 찾음.
- Profile이란? : 아이템을 잘 나타내는 벡터
  - How to Select Important Features? : TF*IDF
    - f(i,j) : Frequenct of term i in document j
    - n(i) : number of docs that mention term i
    - N : 전체 document의 수
    - TF(i,j) = f(i,j)/max(k, f(k,j)) : 그 document에 그 단어가 몇 번 나오는지에 비
    - IDF(i) = log(N/n(i)) : 그 문서에 많이 나오지만, '다른 문서에는 별로 안 나오는 단어'
      - IDF가 크다 : 그 단어가 소수 문서에만 나온다.
      - IDF가 작다 : 그 단어가 많은 문서에 나온다.
    
- User Profile
  - Item Profile의 가중평균
  - 평균과 비교계산 후 가중평균
      
- User Profile을 만든 후, 사용자가 특정 아이템을 얼마나 좋아하는가 예측 : 유사도 측정
  - Cosine Similarity
        
- 장점
  - 1. 다른 사용자의 데이터가 필요하진 않음 : 데이터 부족해도 괜찮
  - 2. 독특한 취향이어도 괜찮
  - 3. 새로운 제품이 나와도 유사도 측정만 하면 되어서 용이
  - 4. 그 점수에 가장 큰 기여를 한 content의 특징을 설명할 수 있음
      
- 단점
  - 1. 유사도 비교 쉽지 않음.
  - 2. 방금 시스템에 가입한 사용자의 user profile 구성 어려움
  - 3. Overfitting
      
## Collaborative Filtering(협력 필터링) 기법
- content를 사용하지 않고, 각 사용자가 제품에 매긴 rating 정보만을 사용한다!
- 파라미터를 데이터에 기반해서 학습하는 방법

- User-User 협업 필터링
  - 사용자의 rating과 같은 rating 매긴 사용자를 찾는다.
  - 예 : rx = {1,0,4,0,1}, ry = {4,0,2,3,0}
    -> Jaccard Similarity = 교집합/합집합 (평점을 무시한다)
    -> Cosine Similarity = 벡터내적 (1과 4를 유사하게 본다)
    -> *Pearson Correlation Coefficient* (평균벡터의 cosine similiarity)
  - 예측방법
    - r(x) : user x의 rating vector
    - N : item I에 대해서 평점을 매긴 사용자들 중 x와 가장 유사한 k명의 사용자를 포함하는 집합
    - r(x) = sigma(r(y))/k
    
    
- Item-Item 협업 필터링
    
## Latent Factor 기법
  - Regularization
  - Bias
  

