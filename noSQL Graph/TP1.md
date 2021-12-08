1. CREATE (TheMatrix:Movie {title:'The Matrix', released:1999, tagline:'Welcome to the Real World'})

2. MATCH (tom {name: "Tom Hanks"}) RETURN tom

3. MATCH (cloudAtlas {title: "Cloud Atlas"}) RETURN cloudAtlas

4. MATCH (people:Person) RETURN people.name LIMIT 10

╒════════════════════╕
│"people.name"       │
╞════════════════════╡
│"Keanu Reeves"      │
├────────────────────┤
│"Carrie-Anne Moss"  │
├────────────────────┤
│"Laurence Fishburne"│
├────────────────────┤
│"Hugo Weaving"      │
├────────────────────┤
│"Lilly Wachowski"   │
├────────────────────┤
│"Lana Wachowski"    │
├────────────────────┤
│"Joel Silver"       │
├────────────────────┤
│"Emil Eifrem"       │
├────────────────────┤
│"Charlize Theron"   │
├────────────────────┤
│"Al Pacino"         │
└────────────────────┘

5. MATCH (nineties:Movie) WHERE nineties.released >= 1990 AND nineties.released < 2000 RETURN nineties.title

╒════════════════════════╕
│"nineties.title"        │
╞════════════════════════╡
│"The Matrix"            │
├────────────────────────┤
│"The Devil's Advocate"  │
├────────────────────────┤
│"A Few Good Men"        │
├────────────────────────┤
│"As Good as It Gets"    │
├────────────────────────┤
│"What Dreams May Come"  │
├────────────────────────┤
│"Snow Falling on Cedars"│
├────────────────────────┤
│"You've Got Mail"       │
├────────────────────────┤
│"Sleepless in Seattle"  │
├────────────────────────┤
│"Joe Versus the Volcano"│
├────────────────────────┤
│"When Harry Met Sally"  │
├────────────────────────┤
│"That Thing You Do"     │
├────────────────────────┤
│"The Birdcage"          │
├────────────────────────┤
│"Unforgiven"            │
├────────────────────────┤
│"Johnny Mnemonic"       │
├────────────────────────┤
│"The Green Mile"        │
├────────────────────────┤
│"Hoffa"                 │
├────────────────────────┤
│"Apollo 13"             │
├────────────────────────┤
│"Twister"               │
├────────────────────────┤
│"Bicentennial Man"      │
├────────────────────────┤
│"A League of Their Own" │
└────────────────────────┘

# QUERY

1. MATCH (tom:Person {name: "Tom Hanks"})-[:ACTED_IN]->(tomHanksMovies) RETURN tom,tomHanksMovies 

2. MATCH (cloudAtlas {title: "Cloud Atlas"})<-[:DIRECTED]-(directors) RETURN directors.name

3. MATCH (tom:Person {name:"Tom Hanks"})-[:ACTED_IN]->(m)<-[:ACTED_IN]-(coActors) RETURN coActors.name

4. MATCH (people:Person)-[relatedTo]-(:Movie {title: "Cloud Atlas"}) RETURN people.name, Type(relatedTo), relatedTo