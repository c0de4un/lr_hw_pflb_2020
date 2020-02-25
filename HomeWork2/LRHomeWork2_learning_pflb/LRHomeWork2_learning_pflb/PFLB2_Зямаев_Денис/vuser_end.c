vuser_end()
{

	// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
	
	web_add_header("X-Requested-With", 
		"XMLHttpRequest");

	web_add_auto_header("dnt", 
		"1");

	// Pause
	lr_think_time( getRnd(1, 100) );
	
	// Transaction.Start
	lr_start_transaction("UC_02_15_logout");
	
	web_url("logout", 
		"URL=http://learning2.pflb.ru:56902/api/logout", 
		"Resource=0", 
		"Referer=http://learning2.pflb.ru:56902/", 
		"Snapshot=t39.inf", 
		"Mode=HTML", 
		LAST);

	// Transaction.Finish
	lr_end_transaction("UC_02_15_logout", LR_AUTO);

	
	web_add_header("Upgrade-Insecure-Requests", 
		"1");

	// Pause
	lr_think_time( getRnd(1, 100) );
	
	// Transaction.Start
	lr_start_transaction("UC_02_16_login_3");
	
	web_url("login_3", 
		"URL=http://learning2.pflb.ru:56902/login", 
		"Resource=0", 
		"RecContentType=text/html", 
		"Referer=http://learning2.pflb.ru:56902/", 
		"Snapshot=t40.inf", 
		"Mode=HTML", 
		LAST);
	
	// Transaction.Finish
	lr_end_transaction("UC_02_16_login_3", LR_AUTO);


	// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
	
	return 0;
}