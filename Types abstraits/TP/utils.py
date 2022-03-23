def question(chaine, char='=', width=20):
    """ Décorateur affichant "Question {chaine}" avant la fonction
    """
    def decorator(func):
        def wrapper(*args, **kwargs):
            print("\n>" + f"< Q{chaine} >".center(width, char) + "<")
            return func(args, kwargs)
        return wrapper
    return decorator