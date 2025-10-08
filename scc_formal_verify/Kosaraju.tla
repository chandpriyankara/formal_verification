---- MODULE Kosaraju ----

EXTENDS Naturals, FiniteSets

CONSTANTS Nodes

VARIABLES visited, sccCount

TypeOK == 
    /\ visited \in [Nodes -> BOOLEAN]
    /\ sccCount \in Nat

Init == 
    /\ visited = [v \in Nodes |-> FALSE]
    /\ sccCount = 0

Next ==
    \/ \E v \in Nodes : /\ visited[v] = FALSE
                       /\ visited' = [visited EXCEPT ![v] = TRUE]
                       /\ sccCount' = sccCount + 1
                       /\ UNCHANGED <<>>

Spec == Init /\ [][Next]_<<visited, sccCount>>

Kosaraju == Spec

(* Invariants *)
Invariant1 == TypeOK
Invariant2 == sccCount <= Cardinality(Nodes)
Invariant3 == DOMAIN visited = Nodes

(* Properties *)
Property1 == sccCount >= 0
Property2 == sccCount <= Cardinality(Nodes)
Property3 == DOMAIN visited = Nodes

====