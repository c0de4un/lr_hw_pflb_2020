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

	// Script Global Transaction.
	lr_start_transaction("UC_01_AOS");
	
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
	
	// Think-Time.
	lr_think_time( rand0m1z3(1, 10) );
	
	// Start Transaction: UC_01_AOS_01_Login
	lr_start_transaction("UC_01_AOS.01_Login");
	
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
	
	// Finish Transaction: UC_01_AOS_01_Login
	lr_end_transaction("UC_01_AOS.01_Login", LR_AUTO);
	
	web_set_sockets_option("INITIAL_AUTH", "BASIC");
	
	// Extract session-id from response.	
	web_reg_save_param_regexp(
		"ParamName=tmp_sid_param",
		"RegExp=JSESSIONID=(\\w+);",
		SEARCH_FILTERS,
		"Scope=Cookies",
		LAST);

	web_reg_save_param_json(
		"ParamName=tmp_session_id_test2",
		"QueryString=$.sessionId",
		"SelectAll=No",
		SEARCH_FILTERS,
		LAST);
	
	// Think-Time.
	lr_think_time( rand0m1z3(1, 10) );
	
	// Start Transaction: UC_01_AOS.02_Browse_Products
	//lr_start_transaction("UC_01_AOS.02_Browse_Products");
	
	web_url("load_carts", 
		"URL=http://advantageonlineshopping.com/order/api/v1/carts/{tmp_uid_param}", 
		"Resource=0", 
		"RecContentType=application/json", 
		"Referer=http://advantageonlineshopping.com/", 
		"Snapshot=t86.inf", 
		"Mode=HTML", 
		LAST);
	
	// Finish Transaction: UC_01_AOS.02_Browse_Products
	//lr_end_transaction("UC_01_AOS.02_Browse_Products", LR_AUTO);

	
	// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
	
	return 0;
}
