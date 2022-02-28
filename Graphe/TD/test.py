def koening(chemin):
    res=[]
    for i in range(len(chemin)):
        if chemin[i] in res:
            del res[res.index(chemin[i])]
        res.append(chemin[i])
    return res