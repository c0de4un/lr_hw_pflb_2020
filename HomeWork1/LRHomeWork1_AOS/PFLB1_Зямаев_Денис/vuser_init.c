/* -------------------------------------------------------------------------------
	Script Title       : 
	Script Description : 
                        
                        
	Recorder Version   : 0
   ------------------------------------------------------------------------------- */

int rand0m1z3(int pMin, int pMax)
{
	if ( pMax < 1 || pMin < 0 )
		return 0;
	
	return (rand() % pMax) + pMin;
}

vuser_init()
{
	// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

	web_add_header("Origin", 
		"http://advantageonlineshopping.com");

	web_add_header("SOAPAction", 
		"com.advantage.online.store.accountserviceAccountLoginRequest");

	web_add_header("X-Requested-With", 
		"XMLHttpRequest");
	
	// Extract user-id from response.	
	web_reg_save_param_xpath(
		"ParamName=tmp_uid_param", 
		"QueryString=/SOAP-ENV:Envelope[1]/SOAP-ENV:Body[1]/ns2:AccountLoginResponse[1]/ns2:StatusMessage[1]/ns2:userId[1]/text()[1]",
		SEARCH_FILTERS,
		"Scope=Body",
		LAST);

	// Base64 Token.
	web_reg_save_param("base_64_token",
		"LB=<ns2:t_authorization>",
		"RB=</ns2:t_authorization>",
		LAST);
	
	// Pause
	lr_think_time( rand0m1z3(1, 10) );
	
	// Transaction.Start
	lr_start_transaction("UC_01_01_AOS_Login");
	
	// Login Request.
	web_custom_request("AccountLoginRequest", 
		"URL=http://advantageonlineshopping.com/accountservice/AccountLoginRequest", 
		"Method=POST", 
		"Resource=0", 
		"RecContentType=text/xml", 
		"Referer=http://advantageonlineshopping.com/", 
		"Snapshot=t85.inf", 
		"Mode=HTML", 
		"EncType=text/xml; charset=UTF-8", 
		"Body=<?xml version=\"1.0\" encoding=\"UTF-8\"?><soap:Envelope xmlns:soap=\"http://schemas.xmlsoap.org/soap/envelope/\" xmlns:xsi=\"http://www.w3.org/2001/XMLSchema-instance\" xmlns:xsd=\"http://www.w3.org/2001/XMLSchema\"><soap:Body><AccountLoginRequest xmlns=\"com.advantage.online.store.accountservice\"><email></email><loginPassword>{pwd}</loginPassword><loginUser>{login}</loginUser></AccountLoginRequest></soap:Body></soap:Envelope>", 
		LAST);
	
	web_set_sockets_option("INITIAL_AUTH", "BASIC");

	// Transaction.Finish
	lr_end_transaction("UC_01_01_AOS_Login", LR_AUTO);
	
	// Extract session-id from response.	
	web_reg_save_param_regexp(
		"ParamName=tmp_sid_param",
		"RegExp=JSESSIONID=(\\w+);",
		SEARCH_FILTERS,
		"Scope=Cookies",
		LAST);

	// Pause
	lr_think_time( rand0m1z3(1, 10) );
	
	// Transaction.Start
	lr_start_transaction("UC_01_02_AOS_Load_Carts");

	web_url("load_carts", 
		"URL=http://advantageonlineshopping.com/order/api/v1/carts/{tmp_uid_param}", 
		"Resource=0", 
		"RecContentType=application/json", 
		"Referer=http://advantageonlineshopping.com/", 
		"Snapshot=t86.inf", 
		"Mode=HTML", 
		LAST);
	
	// Transaction.Finish
	lr_end_transaction("UC_01_02_AOS_Load_Carts", LR_AUTO);
	
	// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
	
	return 0;
}
