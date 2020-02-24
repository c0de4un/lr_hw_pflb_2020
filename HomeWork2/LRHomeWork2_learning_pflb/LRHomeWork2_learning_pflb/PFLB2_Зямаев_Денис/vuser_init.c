/* -------------------------------------------------------------------------------
	Script Title       : 
	Script Description : 
                        
                        
	Recorder Version   : 0
   ------------------------------------------------------------------------------- */

// File Read result.
int res = -1;

/**
 * @brief
 * Generates pseudo random number between min & max.
 * 
 * (!) There is a limitation, min. is 0 & max. is 327xx.
**/
int getRnd( int pMin, int pMax )
{
	if ( pMax < 1 || pMax > 32766 )
		return 0; // Div by 0 exception.
	
	return (rand() % pMax) + pMin;
}

vuser_init()
{
	
	// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

	// Transaction.Start
	lr_start_transaction("UC_02_Incidents_Логин");

	
	// UC_02_PFLB_RaportsSystem_FILE_Input
	//lr_start_transaction("UC_02_PFLB_RaportsSystem_FILE_Input");
	
	// INFO
	//lr_output_message("Testing file input");
	
	// Read file into param.
	//res = lr_read_file("descriptions.txt", "test1", 1);
	
	// INFO
	//lr_output_message("\nFile:\nReaded:%\nContent:%", res, lr_eval_string("{test1}"));
	
	// UC_02_PFLB_RaportsSystem_FILE_Input
	//lr_end_transaction("UC_02_PFLB_RaportsSystem_FILE_Input", LR_AUTO);
	
	// Stop
	//lr_abort();
	
	web_add_cookie("sessionExpired=false; DOMAIN=learning2.pflb.ru");

	web_add_cookie("PFLB.pre.login.link=null; DOMAIN=learning2.pflb.ru");

	web_add_header("Origin", 
		"http://learning2.pflb.ru:56902");

	web_add_auto_header("X-Requested-With", 
		"XMLHttpRequest");

	web_add_auto_header("dnt", 
		"1");

	lr_think_time(4);

	web_submit_data("login_2", 
		"Action=http://learning2.pflb.ru:56902/api/login", 
		"Method=POST", 
		"Referer=http://learning2.pflb.ru:56902/login", 
		"Snapshot=t3.inf", 
		"Mode=HTML", 
		ITEMDATA, 
		"Name=login", "Value=director", ENDITEM, 
		"Name=password", "Value=123", ENDITEM, 
		"Name=rememberMe", "Value=false", ENDITEM, 
		EXTRARES, 
		"Url=../js/core/jqueryformplugin.js?_=1582367837874", "Referer=http://learning2.pflb.ru:56902/", ENDITEM, 
		LAST);

	web_url("checkLogin", 
		"URL=http://learning2.pflb.ru:56902/api/checkLogin", 
		"Resource=0", 
		"RecContentType=application/json", 
		"Referer=http://learning2.pflb.ru:56902/", 
		"Snapshot=t4.inf", 
		"Mode=HTML", 
		LAST);

	web_url("info", 
		"URL=http://learning2.pflb.ru:56902/api/user/info", 
		"Resource=0", 
		"RecContentType=application/json", 
		"Referer=http://learning2.pflb.ru:56902/", 
		"Snapshot=t5.inf", 
		"Mode=HTML", 
		EXTRARES, 
		"Url=/director/wrapper/wrapper.dust", "Referer=http://learning2.pflb.ru:56902/", ENDITEM, 
		"Url=/director/wrapper/wrapper.js", "Referer=http://learning2.pflb.ru:56902/", ENDITEM, 
		LAST);

	web_url("4", 
		"URL=http://learning2.pflb.ru:56902/api/ticket/countByState/4", 
		"Resource=0", 
		"Referer=http://learning2.pflb.ru:56902/", 
		"Snapshot=t6.inf", 
		"Mode=HTML", 
		EXTRARES, 
		"Url=/director/tickets/tickets.dust", "Referer=http://learning2.pflb.ru:56902/", ENDITEM, 
		"Url=/director/tickets/tickets.js", "Referer=http://learning2.pflb.ru:56902/", ENDITEM, 
		LAST);

	web_url("countByState", 
		"URL=http://learning2.pflb.ru:56902/api/ticket/countByState/", 
		"Resource=0", 
		"RecContentType=application/json", 
		"Referer=http://learning2.pflb.ru:56902/", 
		"Snapshot=t7.inf", 
		"Mode=HTML", 
		LAST);

	web_custom_request("ticket", 
		"URL=http://learning2.pflb.ru:56902/api/ticket/?state=-1,0,1,5&page=0&size=10", 
		"Method=GET", 
		"Resource=0", 
		"RecContentType=application/json", 
		"Referer=http://learning2.pflb.ru:56902/", 
		"Snapshot=t22.inf", 
		"Mode=HTML", 
		"EncType=application/json; charset=utf-8", 
		LAST);

	// Transaction.Finish
	lr_end_transaction("UC_02_Incidents_Логин", LR_AUTO);

	// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
	
	
	return 0;
}
