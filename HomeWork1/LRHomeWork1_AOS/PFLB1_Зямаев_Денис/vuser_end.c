vuser_end()
{
	
	// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

	web_add_header("Origin", 
		"http://advantageonlineshopping.com");

	web_add_header("SOAPAction", 
		"com.advantage.online.store.accountserviceAccountLogoutRequest");

	web_add_header("X-Requested-With", 
		"XMLHttpRequest");

	lr_think_time(9);
	
	// Pause
	lr_think_time( rand0m1z3(1, 10) );
	
	// Transaction.Start
	lr_start_transaction("UC_01_19_AOS_AccountLogoutRequest");
	
	web_custom_request("AccountLogoutRequest", 
		"URL=http://advantageonlineshopping.com/accountservice/AccountLogoutRequest", 
		"Method=POST", 
		"Resource=0", 
		"RecContentType=text/xml", 
		"Referer=http://advantageonlineshopping.com/", 
		"Snapshot=t102.inf", 
		"Mode=HTML", 
		"EncType=text/xml; charset=UTF-8", 
		"Body=<?xml version=\"1.0\" encoding=\"UTF-8\"?><soap:Envelope xmlns:soap=\"http://schemas.xmlsoap.org/soap/envelope/\" xmlns:xsi=\"http://www.w3.org/2001/XMLSchema-instance\" xmlns:xsd=\"http://www.w3.org/2001/XMLSchema\"><soap:Body><AccountLogoutRequest xmlns=\"com.advantage.online.store.accountservice\"><loginUser>386165654</loginUser><base64Token>Basic c3Qxbmt5YzBkZTpoYUgxTGs4</base64Token></AccountLogoutRequest></soap:Body></soap:Envelope>", 
		LAST);
	
	lr_end_transaction("UC_01_19_AOS_AccountLogoutRequest", LR_AUTO);
	
	// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
	
	return 0;
}