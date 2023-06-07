import urllib.request as req
from string import printable
import csv
from time import sleep
import contextlib
import re

path = "C:\\Users\\St0negor\\Desktop\\dota_names.csv"
groups = ["https://steamcommunity.com/groups/rottingzxc/members/?p=","https://steamcommunity.com/groups/wgaaabba/members/?p=","https://steamcommunity.com/groups/dota2ru/members/?p=","https://steamcommunity.com/groups/TokyoGhoul/members/?p=","https://steamcommunity.com/groups/Natus-Vincere/members/?p="]
for group in groups:
	print(group)
	try:
		with contextlib.closing(req.urlopen(group)) as page:
			html_bytes = page.read()
			html = html_bytes.decode("utf-8")
			link_pages = re.search("<div class=\"pageLinks\">[\\w\\W]*</div>", html).group(0)
			list_pages = re.findall("p=.\\d*",link_pages)
			total_pages = max(int(n[n.find("=")+1:]) for n in list_pages)
	except:
		print('loading ',group,' failed.')
		
	for n_page in range(1, total_pages+1):
		if((n_page-1)%100 == 0 or n_page == total_pages):
			print(n_page,'/',total_pages)
		url = group + f"{n_page}" 
		try:
			with contextlib.closing(req.urlopen(url)) as page:
				html_bytes = page.read()
				html = html_bytes.decode("utf-8")
				allowed_symbols = '1234567890 !$%^*()_+:?-=<>.'+'qwertyuiopasdfghjklzxcvbnmQWERTYUIOPASDFGHJKLZXCVBNM' + 'йцукенгшщзхъфывапролджэячсмитьбюЙЦУКЕНГШЩЗХЪФЫВАПРОЛДЖЭЯЧСМИТЬБЮ'
				members = re.findall("<a class=\"linkFriend\" .*</a>", html)
				names = []
				for i,member in enumerate(members):
					start_idx = member.find('>')+1
					end_idx = member.find('</a>')
					member = member[start_idx:end_idx]
					if all(c in allowed_symbols for c in member) and len(member)>3:
						names.append(member)
				with open(path, 'a', newline='') as f:
				    writer = csv.writer(f)
				    for name in names:
				    	writer.writerow([name])
		except:
			print('loading page ', n_page,' failed.')
			continue