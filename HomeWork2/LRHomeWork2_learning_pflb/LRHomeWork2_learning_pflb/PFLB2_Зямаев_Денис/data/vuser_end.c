vuser_end()
{

	web_add_header("X-Requested-With", 
		"XMLHttpRequest");

	web_add_auto_header("dnt", 
		"1");

	lr_think_time(4);

	web_url("logout", 
		"URL=http://learning2.pflb.ru:56902/api/logout", 
		"Resource=0", 
		"Referer=http://learning2.pflb.ru:56902/", 
		"Snapshot=t39.inf", 
		"Mode=HTML", 
		LAST);

	web_add_header("Upgrade-Insecure-Requests", 
		"1");

	web_url("login_3", 
		"URL=http://learning2.pflb.ru:56902/login", 
		"Resource=0", 
		"RecContentType=text/html", 
		"Referer=http://learning2.pflb.ru:56902/", 
		"Snapshot=t40.inf", 
		"Mode=HTML", 
		LAST);

	return 0;
}