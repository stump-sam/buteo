# Uniform Random Selection of Combinatorial Objects
## Foreword
- Uniform selection is not always easy.
- Acceptance/rejection can be expensive.
- Aim is to provide efficient *uniform* random selection.


## Random Subsets of `[n]`
- Random subset `S ⊆ [n]`, `|S| = k`, `k`-element subset of `[n]`
- Random subset of `S ⊆ [n]`, `S ∈ 𝒫([n])`, selected `uar` from the power set of `[n]`



## Random Permutations of `[n]`
Random arrangement of the elements of `[n]`, i.e., a bijection from `[n]` to itself.


## Random Compositions of `n` into `k` Parts
Random vector `V = [v_0, v_1, ... v_{k-1}]` such that:
- `|V| = k`
- `v_i >= 0`
- `Σ(i=0,k-1) v[i] == n`
- order matters (vector equivance)


## Random Integer Partitions of `n`
Random vector `V = {v_0, v_1, ..., v_{k-1}}` where:
- `|V| = k`
- `v_i > 0`
- `Σ(i=1,k-1 v_i) == n`
- order does not matter


## Random Set Partitions of `[n]`
Random set of subsets of `[n]`, `S = {S_0, S_1, ..., S_{k-1}}` such that:
- `S_i` are disjoint
- each element `x ∈ [n]`, `x ∈ S_j` for some `j`


