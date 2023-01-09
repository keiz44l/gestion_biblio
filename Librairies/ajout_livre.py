#!/venv/bin/python
import json
#module python pour la lecture et l'ouverture d'URL
from urllib.request import urlopen

import csv



while True:

    #On crée d'un côté la variable liée à l'api (on questionne l'api avec l'isbn ici)
    #Et de l'autre la variable associée à l'isbn que l'on va recevoir ( strip() permet d'enlever les caractères superflus à droite et à gauche de l'isbn)
  api = "https://www.googleapis.com/books/v1/volumes?q=isbn:"
  isbn = input("Entrez l'ISBN ").strip()
  quantity = input("Quelle quantité de ce livre voulez-vous ajouter ? ")
  ligne_a_changer = 0
    #envoie une requête et récupèr la réponse
  resp = urlopen(api + isbn)
    # récupère les données dans un dictionnaire python
  book_data = json.load(resp)

    # create additional variables for easy querying
  volume_info = book_data["items"][0]["volumeInfo"]
  author = volume_info["authors"]
  #Dans le cas où il n'y a pas de catégories indiquées
  try:
    categories = volume_info["categories"]
  except ValueError:
    categories = []
  prettify_author = author if len(author) > 1 else author[0]
  prettify_categories = categories if len(categories) > 1 else categories[0]

    
  liste_livre = [isbn,volume_info['title'], prettify_author, prettify_categories[0], prettify_categories[1], prettify_categories[2], quantity]
    
    #affichage des infos voulues
  print(f"\nTitre: {volume_info['title']}")
  print(f"Auteur: {prettify_author}")
  print(f"Catégories : {prettify_categories}")
  print(f"Quantité : {quantity}")
  print("\n***\n")

    #création bdd csv 
  with open('livres.csv', 'a', newline='') as f:  
      writer = csv.writer(f)
      writer.writerow(liste_livre)
      f.close()
   

  user_update = input("Voulez-vous ajouter un nouveau livre ? (o/n)").lower().strip()

  if user_update != "o":
        break 

