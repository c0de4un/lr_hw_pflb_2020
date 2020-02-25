Action()
{
	
	// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

	// Pause
	lr_think_time( rand0m1z3(1, 10) );
	
	// Transaction.Start
	lr_start_transaction("UC_01_03_AOS_Get_Product_Page");

	web_url("product-page.html", 
		"URL=http://advantageonlineshopping.com/app/views/product-page.html", 
		"Resource=0", 
		"Referer=http://advantageonlineshopping.com/", 
		"Snapshot=t87.inf", 
		"Mode=HTML", 
		LAST);
		
	// Transaction.Finish
	lr_end_transaction("UC_01_03_AOS_Get_Product_Page", LR_AUTO);
	
	web_add_auto_header("Origin", 
		"http://advantageonlineshopping.com");

	// Pause
	lr_think_time( rand0m1z3(1, 10) );
	
	// Transaction.Start
	lr_start_transaction("UC_01_04_AOS_Add_to_Cart");
	
	web_submit_data("3683D1", 
		"Action=http://advantageonlineshopping.com/order/api/v1/carts/{tmp_uid_param}/product/3/color/3683D1?quantity=1", 
		"Method=POST", 
		"RecContentType=application/json", 
		"Referer=http://advantageonlineshopping.com/", 
		"Snapshot=t88.inf", 
		"Mode=HTML", 
		ITEMDATA, 
		"Name=sessionId", "Value={tmp_sid_param}", ENDITEM, 
		LAST);

	// Transaction.End
	lr_end_transaction("UC_01_04_AOS_Add_to_Cart", LR_AUTO);

	web_add_header("SOAPAction", 
		"com.advantage.online.store.accountserviceGetAccountByIdRequest");

	web_add_auto_header("X-Requested-With", 
		"XMLHttpRequest");

	// Pause
	lr_think_time( rand0m1z3(1, 10) );
	
	// Transaction.Start
	lr_start_transaction("UC_01_05_AOS_GetAccountByIdRequest");
	
	web_custom_request("GetAccountByIdRequest", 
		"URL=http://advantageonlineshopping.com/accountservice/GetAccountByIdRequest", 
		"Method=POST", 
		"Resource=0", 
		"RecContentType=text/xml", 
		"Referer=http://advantageonlineshopping.com/", 
		"Snapshot=t89.inf", 
		"Mode=HTML", 
		"EncType=text/xml; charset=UTF-8", 
		"Body=<?xml version=\"1.0\" encoding=\"UTF-8\"?><soap:Envelope xmlns:soap=\"http://schemas.xmlsoap.org/soap/envelope/\" xmlns:xsi=\"http://www.w3.org/2001/XMLSchema-instance\" xmlns:xsd=\"http://www.w3.org/2001/XMLSchema\"><soap:Body><GetAccountByIdRequest xmlns=\"com.advantage.online.store.accountservice\"><accountId>{tmp_uid_param}</accountId><base64Token>Basic {base_64_token}</base64Token></GetAccountByIdRequest></soap:Body></soap:Envelope>", 
		LAST);

	// Transaction.Finish
	lr_end_transaction("UC_01_05_AOS_GetAccountByIdRequest", LR_AUTO);

	
	web_add_header("SOAPAction", 
		"com.advantage.online.store.accountserviceGetAccountByIdNewRequest");

	// Pause
	lr_think_time( rand0m1z3(1, 10) );
	
	// Transaction.Start
	lr_start_transaction("UC_01_06_AOS_GetAccountByIdNewRequest");

	web_custom_request("GetAccountByIdNewRequest", 
		"URL=http://advantageonlineshopping.com/accountservice/GetAccountByIdNewRequest", 
		"Method=POST", 
		"Resource=0", 
		"RecContentType=text/xml", 
		"Referer=http://advantageonlineshopping.com/", 
		"Snapshot=t90.inf", 
		"Mode=HTML", 
		"EncType=text/xml; charset=UTF-8", 
		"Body=<?xml version=\"1.0\" encoding=\"UTF-8\"?><soap:Envelope xmlns:soap=\"http://schemas.xmlsoap.org/soap/envelope/\" xmlns:xsi=\"http://www.w3.org/2001/XMLSchema-instance\" xmlns:xsd=\"http://www.w3.org/2001/XMLSchema\"><soap:Body><GetAccountByIdNewRequest xmlns=\"com.advantage.online.store.accountservice\"><accountId>{tmp_uid_param}</accountId><base64Token>Basic {base_64_token}</base64Token></GetAccountByIdNewRequest></soap:Body></soap:Envelope>", 
		LAST);

	// Transaction.Start
	lr_end_transaction("UC_01_06_AOS_GetAccountByIdNewRequest", LR_AUTO);

	
	web_revert_auto_header("Origin");

	web_revert_auto_header("X-Requested-With");

	// Pause
	lr_think_time( rand0m1z3(1, 10) );
	
	// Transaction.Start
	lr_start_transaction("UC_01_07_AOS_Get_Carts");

	web_url("{tmp_uid_param}_2", 
		"URL=http://advantageonlineshopping.com/order/api/v1/carts/{tmp_uid_param}", 
		"Resource=0", 
		"RecContentType=application/json", 
		"Referer=http://advantageonlineshopping.com/", 
		"Snapshot=t91.inf", 
		"Mode=HTML", 
		LAST);

	// Transaction.Finish
	lr_end_transaction("UC_01_07_AOS_Get_Carts", LR_AUTO);

	web_add_auto_header("Origin", 
		"http://advantageonlineshopping.com");

	// Pause
	lr_think_time( rand0m1z3(1, 10) );
	
	// Transaction.Start
	lr_start_transaction("UC_01_08_AOS_shippingcost");
	
	web_custom_request("shippingcost",
		"URL=http://advantageonlineshopping.com/order/api/v1/shippingcost/",
		"Method=POST",
		"Resource=0",
		"RecContentType=application/json",
		"Referer=http://advantageonlineshopping.com/",
		"Snapshot=t92.inf",
		"Mode=HTML",
		"EncType=application/json;charset=UTF-8",
		"Body={\"seaddress\":{\"addressLine1\":\"Svobody 173\",\"addressLine2\":\"\",\"city\":\"Kazan\",\"country\":\"ru\",\"postalCode\":426000,\"state\":\"Tataria\"},\"secustomerName\":\"Denis Zaicev\",\"secustomerPhone\":\"8-800-555-4221\",\"senumberOfProducts\":1,\"setransactionType\":\"SHIPPING_COST\",\"sessionId\":\"{CorrelationParameter}\"}",
		LAST);

	// Transaction.End
	lr_end_transaction("UC_01_08_AOS_shippingcost", LR_AUTO);
	
	web_add_header("SOAPAction", 
		"com.advantage.online.store.accountserviceGetAccountPaymentPreferencesRequest");

	web_add_header("X-Requested-With", 
		"XMLHttpRequest");

	// Pause
	lr_think_time( rand0m1z3(1, 10) );
	
	// Transaction.Start
	lr_start_transaction("UC_01_10_AOS_GetAccountPaymentPreferencesRequest");
	
	web_custom_request("GetAccountPaymentPreferencesRequest", 
		"URL=http://advantageonlineshopping.com/accountservice/GetAccountPaymentPreferencesRequest", 
		"Method=POST", 
		"Resource=0", 
		"RecContentType=text/xml", 
		"Referer=http://advantageonlineshopping.com/", 
		"Snapshot=t93.inf", 
		"Mode=HTML", 
		"EncType=text/xml; charset=UTF-8", 
		"Body=<?xml version=\"1.0\" encoding=\"UTF-8\"?><soap:Envelope xmlns:soap=\"http://schemas.xmlsoap.org/soap/envelope/\" xmlns:xsi=\"http://www.w3.org/2001/XMLSchema-instance\" xmlns:xsd=\"http://www.w3.org/2001/XMLSchema\"><soap:Body><GetAccountPaymentPreferencesRequest xmlns=\"com.advantage.online.store.accountservice\"><accountId>{tmp_uid_param}</accountId><base64Token>Basic {base_64_token}</base64Token></GetAccountPaymentPreferencesRequest></soap:Body></soap:Envelope>", 
		LAST);

	// Transaction.Finish
	lr_end_transaction("UC_01_10_AOS_GetAccountPaymentPreferencesRequest", LR_AUTO);

	web_revert_auto_header("Origin");

	// Pause
	lr_think_time( rand0m1z3(1, 10) );
	
	// Transaction.Start
	lr_start_transaction("UC_01_11_AOS_Load_orderPayment_page");

	web_url("orderPayment-page.html", 
		"URL=http://advantageonlineshopping.com/app/order/views/orderPayment-page.html", 
		"Resource=0", 
		"Referer=http://advantageonlineshopping.com/", 
		"Snapshot=t94.inf", 
		"Mode=HTML", 
		LAST);

	// Transaction.Finish
	lr_end_transaction("UC_01_11_AOS_Load_orderPayment_page", LR_AUTO);

	
	web_add_header("SOAPAction", 
		"com.advantage.online.store.accountserviceGetCountriesRequest");

	web_add_auto_header("Origin", 
		"http://advantageonlineshopping.com");

	web_add_auto_header("X-Requested-With", 
		"XMLHttpRequest");

	// Pause
	lr_think_time( rand0m1z3(1, 10) );
	
	// Transaction.Start
	lr_start_transaction("UC_01_12_AOS_GetCountriesRequest");
	
	web_custom_request("GetCountriesRequest", 
		"URL=http://advantageonlineshopping.com/accountservice/GetCountriesRequest", 
		"Method=POST", 
		"Resource=0", 
		"RecContentType=text/xml", 
		"Referer=http://advantageonlineshopping.com/", 
		"Snapshot=t95.inf", 
		"Mode=HTML", 
		"EncType=text/xml; charset=UTF-8", 
		"Body=<?xml version=\"1.0\" encoding=\"UTF-8\"?><soap:Envelope xmlns:soap=\"http://schemas.xmlsoap.org/soap/envelope/\" xmlns:xsi=\"http://www.w3.org/2001/XMLSchema-instance\" xmlns:xsd=\"http://www.w3.org/2001/XMLSchema\"><soap:Body><GetCountriesRequest xmlns=\"com.advantage.online.store.accountservice\"></GetCountriesRequest></soap:Body></soap:Envelope>", 
		LAST);

	// Transaction.Finish
	lr_end_transaction("UC_01_12_AOS_GetCountriesRequest", LR_AUTO);

	
	web_add_header("SOAPAction", 
		"com.advantage.online.store.accountserviceAccountUpdateRequest");

	// Pause
	lr_think_time( rand0m1z3(1, 10) );
	
	// Transaction.Start
	lr_start_transaction("UC_01_13_AOS_AccountUpdateRequest");
	
	web_custom_request("AccountUpdateRequest", 
		"URL=http://advantageonlineshopping.com/accountservice/AccountUpdateRequest", 
		"Method=POST", 
		"Resource=0", 
		"RecContentType=text/xml", 
		"Referer=http://advantageonlineshopping.com/", 
		"Snapshot=t96.inf", 
		"Mode=HTML", 
		"EncType=text/xml; charset=UTF-8", 
		"Body=<?xml version=\"1.0\" encoding=\"UTF-8\"?><soap:Envelope xmlns:soap=\"http://schemas.xmlsoap.org/soap/envelope/\" xmlns:xsi=\"http://www.w3.org/2001/XMLSchema-instance\" xmlns:xsd=\"http://www.w3.org/2001/XMLSchema\"><soap:Body><AccountUpdateRequest xmlns=\"com.advantage.online.store.accountservice\"><lastName>Zaicev</lastName><firstName>Denis</firstName><accountId>{tmp_uid_param}</accountId><countryId>Russia,ru</countryId><stateProvince>Tataria</stateProvince><cityName>Kazan</cityName><address"
		">Svobody 173</address><zipcode>426000</zipcode><phoneNumber>8-800-555-4221</phoneNumber><email>{login}@yandex.ru</email><accountType>20</accountType><allowOffersPromotion>true</allowOffersPromotion></AccountUpdateRequest></soap:Body></soap:Envelope>", 
		LAST);

	// Transaction.Finish
	lr_end_transaction("UC_01_13_AOS_AccountUpdateRequest", LR_AUTO);

	
	web_revert_auto_header("Origin");

	web_revert_auto_header("X-Requested-With");

	// Pause
	lr_think_time( rand0m1z3(1, 10) );
	
	// Transaction.Start
	lr_start_transaction("UC_01_14_AOS_Get_Carts");
	
	web_url("{tmp_uid_param}_3", 
		"URL=http://advantageonlineshopping.com/order/api/v1/carts/{tmp_uid_param}", 
		"Resource=0", 
		"RecContentType=application/json", 
		"Referer=http://advantageonlineshopping.com/", 
		"Snapshot=t97.inf", 
		"Mode=HTML", 
		LAST);

	// Transaction.Finish
	lr_end_transaction("UC_01_14_AOS_Get_Carts", LR_AUTO);

	
	web_add_auto_header("Origin", 
		"http://advantageonlineshopping.com");

	// Pause
	lr_think_time( rand0m1z3(1, 10) );
	
	// Transaction.Start
	lr_start_transaction("UC_01_15_AOS_shippingcost_2");
	
	web_custom_request("shippingcost_2", 
		"URL=http://advantageonlineshopping.com/order/api/v1/shippingcost/", 
		"Method=POST", 
		"Resource=0", 
		"RecContentType=application/json", 
		"Referer=http://advantageonlineshopping.com/", 
		"Snapshot=t98.inf", 
		"Mode=HTML", 
		"EncType=application/json;charset=UTF-8", 
		"Body={\"seaddress\":{\"addressLine1\":\"Svobody 173\",\"addressLine2\":\"\",\"city\":\"Kazan\",\"country\":\"ru\",\"postalCode\":426000,\"state\":\"Tataria\"},\"secustomerName\":\"Denis Zaicev\",\"secustomerPhone\":\"8-800-555-4221\",\"senumberOfProducts\":1,\"setransactionType\":\"SHIPPING_COST\",\"sessionId\":\"{sid}\"}", 
		LAST);

	// Transaction.Finish
	lr_end_transaction("UC_01_15_AOS_shippingcost_2", LR_AUTO);

	
	web_add_header("SOAPAction", 
		"com.advantage.online.store.accountserviceUpdateSafePayMethodRequest");

	web_add_header("X-Requested-With", 
		"XMLHttpRequest");

	// Pause
	lr_think_time( rand0m1z3(1, 10) );
	
	// Transaction.Start
	lr_start_transaction("UC_01_16_AOS_UpdateSafePayMethodRequest");
	
	web_custom_request("UpdateSafePayMethodRequest", 
		"URL=http://advantageonlineshopping.com/accountservice/UpdateSafePayMethodRequest", 
		"Method=POST", 
		"Resource=0", 
		"RecContentType=text/xml", 
		"Referer=http://advantageonlineshopping.com/", 
		"Snapshot=t99.inf", 
		"Mode=HTML", 
		"EncType=text/xml; charset=UTF-8", 
		"Body=<?xml version=\"1.0\" encoding=\"UTF-8\"?><soap:Envelope xmlns:soap=\"http://schemas.xmlsoap.org/soap/envelope/\" xmlns:xsi=\"http://www.w3.org/2001/XMLSchema-instance\" xmlns:xsd=\"http://www.w3.org/2001/XMLSchema\"><soap:Body><UpdateSafePayMethodRequest xmlns=\"com.advantage.online.store.accountservice\"><userId>{tmp_uid_param}</userId><safePayUsername>{login}</safePayUsername><safePayPassword>bb0a2425a6bf</safePayPassword><referenceId>1234567890</referenceId><base64Token>Basic "
		"{base_64_token}</base64Token></UpdateSafePayMethodRequest></soap:Body></soap:Envelope>", 
		LAST);

	// Transaction.Finish
	lr_end_transaction("UC_01_16_AOS_UpdateSafePayMethodRequest", LR_AUTO);

	// Pause
	lr_think_time( rand0m1z3(1, 10) );
	
	// Transaction.Start
	lr_start_transaction("UC_01_17_AOS_Send_Paymant_Data");
	
	web_custom_request("{tmp_uid_param}_4", 
		"URL=http://advantageonlineshopping.com/order/api/v1/orders/users/{tmp_uid_param}", 
		"Method=POST", 
		"Resource=0", 
		"RecContentType=application/json", 
		"Referer=http://advantageonlineshopping.com/", 
		"Snapshot=t100.inf", 
		"Mode=HTML", 
		"EncType=application/json", 
		"Body={\"orderPaymentInformation\":{\"Transaction_AccountNumber\":\"843200971\",\"Transaction_Currency\":\"USD\",\"Transaction_CustomerPhone\":\"8-800-555-4221\",\"Transaction_MasterCredit_CVVNumber\":\"\",\"Transaction_MasterCredit_CardNumber\":\"4886\",\"Transaction_MasterCredit_CustomerName\":\"\",\"Transaction_MasterCredit_ExpirationDate\":\"122027\",\"Transaction_PaymentMethod\":\"SafePay\",\"Transaction_ReferenceNumber\":0,\"Transaction_SafePay_Password\":\""
		"bb0a2425a6bf479d56ba89dbb18c5001ce0f6594\",\"Transaction_SafePay_UserName\":\"{login}\",\"Transaction_TransactionDate\":\"21022020\",\"Transaction_Type\":\"PAYMENT\"},\"orderShippingInformation\":{\"Shipping_Address_Address\":\"Svobody 173\",\"Shipping_Address_City\":\"Kazan\",\"Shipping_Address_CountryCode\":\"Russia,ru\",\"Shipping_Address_CustomerName\":\"Denis Zaicev\",\"Shipping_Address_CustomerPhone\":\"8-800-555-4221\",\"Shipping_Address_PostalCode\":426000,\"Shipping_Address_State\":\""
		"Tataria\",\"Shipping_Cost\":449.99,\"Shipping_NumberOfProducts\":1,\"Shipping_TrackingNumber\":0},\"purchasedProducts\":[{\"hexColor\":\"3683D1\",\"productId\":3,\"quantity\":1}]}", 
		LAST);

	// Transaction.Finish
	lr_end_transaction("UC_01_17_AOS_Send_Paymant_Data", LR_AUTO);
	
	// Pause
	lr_think_time( rand0m1z3(1, 10) );
	
	// Transaction.Start
	lr_start_transaction("UC_01_18_AOS_Clear_Cart");
	
	web_custom_request("{tmp_uid_param}_5", 
		"URL=http://advantageonlineshopping.com/order/api/v1/carts/{tmp_uid_param}", 
		"Method=DELETE", 
		"Resource=0", 
		"RecContentType=application/json", 
		"Referer=http://advantageonlineshopping.com/", 
		"Snapshot=t101.inf", 
		"Mode=HTML", 
		LAST);

	// Transaction.Finish
	lr_end_transaction("UC_01_18_AOS_Clear_Cart", LR_AUTO);
	
	// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
	
	return 0;
}
