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
	
	web_add_cookie("sessionExpired=false; DOMAIN=learning2.pflb.ru");

	web_add_cookie("PFLB.pre.login.link=null; DOMAIN=learning2.pflb.ru");

	web_add_header("Origin", 
		"http://learning2.pflb.ru:56902");

	web_add_auto_header("X-Requested-With", 
		"XMLHttpRequest");

	web_add_auto_header("dnt", 
		"1");

	// Pause
	lr_think_time( getRnd(1, 100) );
	
	// Transaction.Start
	lr_start_transaction("UC_02_01_IncidentsDirector_Логин");

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

	// Transaction.Finish
	lr_end_transaction("UC_02_01_IncidentsDirector_Логин", LR_AUTO);

	// Pause
	lr_think_time( getRnd(1, 100) );
	
	// Transaction.Start
	lr_start_transaction("UC_02_02_IncidentsDirector_checkLogin");
	
	web_url("checkLogin", 
		"URL=http://learning2.pflb.ru:56902/api/checkLogin", 
		"Resource=0", 
		"RecContentType=application/json", 
		"Referer=http://learning2.pflb.ru:56902/", 
		"Snapshot=t4.inf", 
		"Mode=HTML", 
		LAST);
	
	// Transaction.Finish
	lr_end_transaction("UC_02_02_IncidentsDirector_checkLogin", LR_AUTO);

	// Pause
	lr_think_time( getRnd(1, 100) );
	
	// Transaction.Start
	lr_start_transaction("UC_02_03_IncidentsDirector_Get_UserInfo");
	
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

	// Transaction.Finish
	lr_end_transaction("UC_02_03_IncidentsDirector_Get_UserInfo", LR_AUTO);

	// Pause
	lr_think_time( getRnd(1, 100) );
	
	// Transaction.Start
	lr_start_transaction("UC_02_04_IncidentsDirector_countByState_4");
	
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

	// Transaction.Finish
	lr_end_transaction("UC_02_04_IncidentsDirector_countByState_4", LR_AUTO);
	
	// Pause
	lr_think_time( getRnd(1, 100) );
	
	// Transaction.Start
	lr_start_transaction("UC_02_05_IncidentsDirector_ticket_countByState");
	
	web_url("countByState", 
		"URL=http://learning2.pflb.ru:56902/api/ticket/countByState/", 
		"Resource=0", 
		"RecContentType=application/json", 
		"Referer=http://learning2.pflb.ru:56902/", 
		"Snapshot=t7.inf", 
		"Mode=HTML", 
		LAST);
	
	// Transaction.Finish
	lr_end_transaction("UC_02_05_IncidentsDirector_ticket_countByState", LR_AUTO);

	// Pause
	lr_think_time( getRnd(1, 100) );
	
	// Transaction.Start
	lr_start_transaction("UC_02_06_IncidentsDirector_get_ticket");
	
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
	lr_end_transaction("UC_02_06_IncidentsDirector_get_ticket", LR_AUTO);

	// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
	
	
	return 0;
}
