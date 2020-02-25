/**
 * Approximetely web-response nodes structure:
 * root [Level#1]
 *  - (root).node [Level#2]
 *     - (root.node.node).node [Level#3]
 *        - (root.node.node.service) Services [Level#4]
 *  - (root).node [Level#2]
 *     - (root.node.service) Services [Level#3]
**/


// Nodes counters.
int rootNodesNum;
int lvl2NodesNum;
int lvl3NodesNum;
int lvl4NodesNum;

// Random Node-indices.
int rootNodeIdx;
int rootNodeID;
int lvl2NodeIdx;
int lvl2NodeID;
int lvl3NodeIdx;
int lvl3NodeID;
int lvl4NodeIdx;
int lvl4NodeID;

/*
 *
 * (?) Notes:
 *  - not all services contained inside of the 3-Level nodes. Some nodes are
 *  only 2 level, then goest services list (except #5 root, where it is empty).
 *  When logic eaches the such node, it skips it and goes straight to the services ;
 *  - there is some bug with functionality of the last #5 root-node, so it's just ignored, maybe there is a workaround ;
 *  - it is preffered to use 'sprintf' instead of the 'lr_param_sprintf' due to easier usage os c-string
 *    + official docs. of Microfocus says the exact same ;
 *  - in JS there is some bug, so record always contains empty response for structure (raport ?), though it is
 *    not relevant, because manual request allows to avoid UI/UX usage at all ;
 *  - random goes from 1 to n, not from 0 to n-1 as usual ;
*/

/*
 * C-String representation of the Nodes array element index.
 * Used to concat node indices array name with specific index ( "myArray_{index}" ).
 * Since stack memory space is limited per variable up to 256 bytes, this value has limited size.
 * It is known, that indices are from xxx up to xxxx symbols.
*/
char arrIndexStr[5];

/**
 * Well, this c-string used to cache indexes of array, as int.
 * Allows to concat with JSON requests via lr_eval_string.
**/
char nodeIndexStr[5];

Action()
{

	// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

	// Initialize Randomizer.
	srand(time(NULL));
	
	web_add_cookie("filterSetting=%7B%22page%22%3A%22http%3A%2F%2Flearning2.pflb.ru%3A56902%2F%23tickets%3Fstate%3Dopened%26page%3D1%22%2C%22smho%22%3Anull%2C%22dateStart%22%3A%22%22%2C%22dateEnd%22%3A%22%22%2C%22cat1%22%3Anull%2C%22cat2%22%3Anull%2C%22cat3%22%3Anull%2C%22cat4%22%3Anull%2C%22theme%22%3Anull%2C%22overdue%22%3Afalse%2C%22filters%22%3A%7B%22newCheckbox%22%3Atrue%2C%22appointedCheckbox%22%3Atrue%2C%22performedCheckbox%22%3Atrue%2C%22controlCheckbox%22%3Atrue%7D%7D; DOMAIN=learning2.pflb.ru");

	web_add_auto_header("X-Requested-With", 
		"XMLHttpRequest");

	web_add_auto_header("dnt", 
		"1");
	
	// Get array of root indices.
	web_reg_save_param_json(
		"ParamName=Root_IDs",
		"QueryString=$.[*].id",
		"SelectAll=Yes",
		SEARCH_FILTERS,
		LAST);
	
	// Pause
	lr_think_time( getRnd(1, 100) );
	
	// Transaction.Start
	lr_start_transaction("UC_02_07_get_root");
	
	// Get Root-Categories. (Level #1)
	web_url("children", 
		"URL=http://learning2.pflb.ru:56902/api/user/catalog/node/0/children/", 
		"Resource=0", 
		"RecContentType=application/json", 
		"Referer=http://learning2.pflb.ru:56902/", 
		"Snapshot=t25.inf", 
		"Mode=HTML", 
		LAST);

	// Transaction.Finish
	lr_end_transaction("UC_02_07_get_root", LR_AUTO);

	
	// Root Elements Count.
	rootNodesNum = atoi(lr_eval_string("{Root_IDs_count}")) - 1; // Last #5 Root-Node is not functional.
	
	// Get Random Root element index.
	rootNodeIdx = getRnd(1, rootNodesNum); //rand() % rootNodesNum;
	
	// Get Random Root.ID from Array.
	sprintf( arrIndexStr, "{Root_IDs_%d}", rootNodeIdx );
	
	// integer to c-string
	sprintf( nodeIndexStr, "%d", rootNodeIdx );
	
	// INFO
	lr_output_message("Root Size:%d", rootNodesNum);
	lr_output_message("Root Node Index:%d", rootNodeIdx);
	lr_output_message("ID: %s", lr_eval_string(arrIndexStr));
	
	// Copy C-String with Node ID to the Param (Required for URL).
	lr_save_string( lr_eval_string(arrIndexStr), "node_id");
	
	// Copy C-String with Node Index to the Param (Required for JSON-Query).
	lr_save_string( lr_eval_string(nodeIndexStr), "node_idx");
	
	// Pause
	lr_think_time( getRnd(1, 100) );
	
	// Transaction.Start
	lr_start_transaction("UC_02_08_get_treeview");
	
	// Complete Structure Request.
	web_url("treeview", 
		"URL=http://learning2.pflb.ru:56902/api/user/catalog/treeview", 
		"Resource=0", 
		"RecContentType=application/json", 
		"Referer=http://learning2.pflb.ru:56902/", 
		"Snapshot=t26.inf", 
		"Mode=HTML", 
		EXTRARES, 
		"Url=/director/catalog/catalog.dust", "Referer=http://learning2.pflb.ru:56902/", ENDITEM, 
		"Url=/director/catalog/catalog.js", "Referer=http://learning2.pflb.ru:56902/", ENDITEM, 
		LAST);
	
	// Transaction.Finish
	lr_end_transaction("UC_02_08_get_treeview", LR_AUTO);
	
	// Get array of Level3 Nodes using JSON.
	web_reg_save_param_json(
		"ParamName=Lvl2_IDs",
		"QueryString=$.[*].id",
		"SelectAll=Yes",
		"Notfound=error",
		SEARCH_FILTERS,
		LAST);
	
	// Random Pause.
	lr_think_time(getRnd(5, 20));
	
	// Level #2
	
	// Pause
	lr_think_time( getRnd(1, 100) );
	
	// Transaction.Start
	lr_start_transaction("UC_02_09_get_lvl2");
	
	// Request Level #2 [root.node] Structure
	web_url("children_2", 
		"URL=http://learning2.pflb.ru:56902/api/user/catalog/node/{node_id}/children/", 
		"Resource=0", 
		"RecContentType=application/json", 
		"Referer=http://learning2.pflb.ru:56902/", 
		"Snapshot=t27.inf", 
		"Mode=HTML", 
		LAST);

	// Transaction.Finish
	lr_end_transaction("UC_02_09_get_lvl2", LR_AUTO);
	
	// Root.Node Elements Count.
	lvl2NodesNum = atoi(lr_eval_string("{Lvl2_IDs_count}"));
	
	// Get Random Lvl2 Index.
	lvl2NodeIdx = getRnd(1, lvl2NodesNum);
	
	// Get Node Index from Array.
	sprintf( arrIndexStr, "{Lvl2_IDs_%d}", lvl2NodeIdx );
	
	// Llv2 Node Index (!=ID) to c-string
	sprintf( nodeIndexStr, "%d", lvl2NodeIdx );
	
	// INFO
	lr_output_message("Lvl2 Size:%d", rootNodesNum);
	lr_output_message("Lvl2 Node Index:%d", rootNodeIdx);
	lr_output_message("Lvl2 ID: %s", lr_eval_string(arrIndexStr));
	
	// Copy C-String with Node ID to the Param.
	lr_save_string( lr_eval_string(arrIndexStr), "node_id");
	
	// Copy C-String with Node Index to the Param (Required for JSON-Query).
	lr_save_string( lr_eval_string(nodeIndexStr), "node_idx");
	
	// Random Pause.
	lr_think_time(getRnd(5, 20));
	
	// Level #3
	
	// Get array of Level3 Nodes using JSON.
	web_reg_save_param_json(
		"ParamName=Lvl3_IDs",
		"QueryString=$.[*].id",
		"SelectAll=Yes",
		"Notfound=warning", // Disable exception throw, because Lvl3 could not have sub-nodes, it is expected.
		SEARCH_FILTERS,
		LAST);
	
	// Pause
	lr_think_time( getRnd(1, 100) );
	
	// Transaction.Start
	lr_start_transaction("UC_02_10_get_lvl3_nodes");
	
	// Level #3 [root.node.node]
	web_url("children_3", 
		"URL=http://learning2.pflb.ru:56902/api/user/catalog/node/{node_id}/children/", 
		"Resource=0", 
		"RecContentType=application/json", 
		"Referer=http://learning2.pflb.ru:56902/", 
		"Snapshot=t27.inf", 
		"Mode=HTML", 
		LAST);
	
	// Transaction.Finish
	lr_end_transaction("UC_02_10_get_lvl3_nodes", LR_AUTO);
	
	// Root.Node.Node Elements Count.
	lvl3NodesNum = atoi(lr_eval_string("{Lvl3_IDs_count}"));
	
	// Level #3 has Nodes or Services ?
	if ( lvl3NodesNum > 0 )
	{
		// Get Random Lvl3 Index.
		lvl3NodeIdx = getRnd(1, lvl3NodesNum);
	
		// Get Node Index from Array.
		sprintf( arrIndexStr, "{Lvl3_IDs_%d}", lvl3NodeIdx );
	
		// Llv3 Node Index (!=ID) to c-string
		sprintf( nodeIndexStr, "%d", lvl3NodeIdx );
	
		// INFO
		lr_output_message("Lvl3 Size:%d", rootNodesNum);
		lr_output_message("Lvl3 Node Index:%d", rootNodeIdx);
		lr_output_message("Lvl3 ID: %s", lr_eval_string(arrIndexStr));
	
		// Copy C-String with Node ID to the Param.
		lr_save_string( lr_eval_string(arrIndexStr), "node_id");
	
		// Copy C-String with Node Index to the Param (Required for JSON-Query).
		lr_save_string( lr_eval_string(nodeIndexStr), "node_idx");
	} ///
	else
	{
		// INFO
		lr_output_message("Lvll3 doesn't have sub-nodes, only services.");
	}
	
	// Level #4 (Services)
	
	// Random Pause.
	lr_think_time(getRnd(5, 20));
	
	// Get array of Level4 Nodes using JSON.
	web_reg_save_param_json(
		"ParamName=Lvl4_IDs",
		"QueryString=$.[*].id",
		"SelectAll=Yes",
		"Notfound=error",
		SEARCH_FILTERS,
		LAST);
	
	// Pause
	lr_think_time( getRnd(1, 100) );
	
	// Transaction.Start
	lr_start_transaction("UC_02_11_get_services");
	
	// Level #4 [root.node.node.node]
	web_url("children_4", 
		"URL=http://learning2.pflb.ru:56902/api/user/catalog/node/{node_id}/service/", 
		"Resource=0", 
		"RecContentType=application/json", 
		"Referer=http://learning2.pflb.ru:56902/", 
		"Snapshot=t28.inf", 
		"Mode=HTML", 
		LAST);
	
	// Transaction.Finish
	lr_end_transaction("UC_02_11_get_services", LR_AUTO);
	
	// Root.Node.Node Elements Count.
	lvl4NodesNum = atoi(lr_eval_string("{Lvl4_IDs_count}"));
	
	// Root.Node.Node Elements Count.
	lvl4NodesNum = atoi(lr_eval_string("{Lvl4_IDs_count}"));
	
	// Get Random Lvl4 Index.
	lvl4NodeIdx = getRnd(1, lvl4NodesNum);
	
	// Get Node Index from Array.
	sprintf( arrIndexStr, "{Lvl4_IDs_%d}", lvl4NodeIdx );
	
	// Llv3 Node Index (!=ID) to c-string
	sprintf( nodeIndexStr, "%d", lvl4NodeIdx );
	
	// INFO
	lr_output_message("Lvl4 Size:%d", rootNodesNum);
	lr_output_message("Lvl4 Node Index:%d", rootNodeIdx);
	lr_output_message("Lvl4 ID: %s", lr_eval_string(arrIndexStr));
	
	// Copy C-String with Node ID to the Param.
	//lr_save_string( lr_eval_string(arrIndexStr), "node_id");
	lr_save_string( lr_eval_string(arrIndexStr), "service_id");
	
	// Copy C-String with Node Index to the Param (Required for JSON-Query).
	lr_save_string( lr_eval_string(nodeIndexStr), "node_idx");
	
	// Random pause.
	lr_think_time(getRnd(3, 20));
	
	// Not required.
//	web_url("", 
//		"URL=http://learning2.pflb.ru:56902/api/user/catalog/breadcrumbs/{node_id}", 
//		"Resource=0", 
//		"RecContentType=application/json", 
//		"Referer=http://learning2.pflb.ru:56902/", 
//		"Snapshot=t29.inf", 
//		"Mode=HTML", 
//		EXTRARES, 
//		"Url=/director/addticket.dust", "Referer=http://learning2.pflb.ru:56902/", ENDITEM, 
//		LAST);

	// Pause
	lr_think_time( getRnd(1, 100) );
	
	// Transaction.Start
	lr_start_transaction("UC_02_12_get_inventoryNumbers_for_service");
	
	web_url("inventoryNumbers", 
		"URL=http://learning2.pflb.ru:56902/api/inventoryNumbers?serviceId={service_id}", 
		"Resource=0", 
		"RecContentType=application/json", 
		"Referer=http://learning2.pflb.ru:56902/", 
		"Snapshot=t30.inf", 
		"Mode=HTML", 
		LAST);

	// Transaction.Finish
	lr_end_transaction("UC_02_12_get_inventoryNumbers_for_service", LR_AUTO);

	web_add_header("Origin", 
		"http://learning2.pflb.ru:56902");

	lr_think_time(7);
	
	// Not really required, but, if input is CP-1251 and output is UTF-8.
	//lr_convert_string_encoding( lr_eval_string("{incident_custom_description}"), LR_ENC_UTF8, LR_ENC_UTF8, "utf8Msg" );

	// Pause
	lr_think_time( getRnd(1, 100) );
	
	// Transaction.Start
	lr_start_transaction("UC_02_13_post_ticket");
	
	// Request Random Service (Level#4: root.node.node.node).
	web_custom_request("ticket_2", 
		"URL=http://learning2.pflb.ru:56902/api/ticket/", 
		"Method=POST", 
		"Resource=0", 
		"RecContentType=application/json", 
		"Referer=http://learning2.pflb.ru:56902/", 
		"Snapshot=t31.inf", 
		"Mode=HTML", 
		"EncType=application/json; charset=UTF-8", 
		"BodyBinary={\"text\":\"{incident_custom_description}\",\"header\":\"{incident_custom_description}\",\"ticketStateId\":0,\"serviceId\":\"{service_id}\",\"files\":[],\"inventoryNumberId\":null}", 
		LAST);

	//
	lr_end_transaction("UC_02_13_post_ticket", LR_AUTO);

	
	// Not Required.
//	web_url("checkLogin_2", 
//		"URL=http://learning2.pflb.ru:56902/api/checkLogin", 
//		"Resource=0", 
//		"RecContentType=application/json", 
//		"Referer=http://learning2.pflb.ru:56902/", 
//		"Snapshot=t32.inf", 
//		"Mode=HTML", 
//		EXTRARES, 
//		"Url=../js/core/jqueryformplugin.js?_=1582367862805", "Referer=http://learning2.pflb.ru:56902/", ENDITEM, 
//		LAST);
//
//	web_url("info_2", 
//		"URL=http://learning2.pflb.ru:56902/api/user/info", 
//		"Resource=0", 
//		"RecContentType=application/json", 
//		"Referer=http://learning2.pflb.ru:56902/", 
//		"Snapshot=t33.inf", 
//		"Mode=HTML", 
//		EXTRARES, 
//		"Url=/director/wrapper/wrapper.dust", "Referer=http://learning2.pflb.ru:56902/", ENDITEM, 
//		"Url=/director/wrapper/wrapper.js", "Referer=http://learning2.pflb.ru:56902/", ENDITEM, 
//		LAST);
//
//	web_url("4_2", 
//		"URL=http://learning2.pflb.ru:56902/api/ticket/countByState/4", 
//		"Resource=0", 
//		"Referer=http://learning2.pflb.ru:56902/", 
//		"Snapshot=t34.inf", 
//		"Mode=HTML", 
//		EXTRARES, 
//		"Url=/director/tickets/tickets.dust", "Referer=http://learning2.pflb.ru:56902/", ENDITEM, 
//		"Url=/director/tickets/tickets.js", "Referer=http://learning2.pflb.ru:56902/", ENDITEM, 
//		LAST);
//
//	web_url("countByState_2", 
//		"URL=http://learning2.pflb.ru:56902/api/ticket/countByState/", 
//		"Resource=0", 
//		"RecContentType=application/json", 
//		"Referer=http://learning2.pflb.ru:56902/", 
//		"Snapshot=t35.inf", 
//		"Mode=HTML", 
//		LAST);
//
//	web_custom_request("ticket_3", 
//		"URL=http://learning2.pflb.ru:56902/api/ticket/?state=-1,0,1,5&page=0&size=10", 
//		"Method=GET", 
//		"Resource=0", 
//		"RecContentType=application/json", 
//		"Referer=http://learning2.pflb.ru:56902/", 
//		"Snapshot=t36.inf", 
//		"Mode=HTML", 
//		"EncType=application/json; charset=utf-8", 
//		EXTRARES, 
//		"Url=/director/tickets/tickets.dust", "Referer=http://learning2.pflb.ru:56902/", ENDITEM, 
//		"Url=/director/tickets/tickets.js", "Referer=http://learning2.pflb.ru:56902/", ENDITEM, 
//		LAST);
//
//	web_url("countByState_3", 
//		"URL=http://learning2.pflb.ru:56902/api/ticket/countByState/", 
//		"Resource=0", 
//		"RecContentType=application/json", 
//		"Referer=http://learning2.pflb.ru:56902/", 
//		"Snapshot=t37.inf", 
//		"Mode=HTML", 
//		LAST);
//
//	web_custom_request("ticket_4", 
//		"URL=http://learning2.pflb.ru:56902/api/ticket/?state=-1,0,1,5&page=0&size=10", 
//		"Method=GET", 
//		"Resource=0", 
//		"RecContentType=application/json", 
//		"Referer=http://learning2.pflb.ru:56902/", 
//		"Snapshot=t38.inf", 
//		"Mode=HTML", 
//		"EncType=application/json; charset=utf-8", 
//		LAST);

	// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
	
	
	return 0;
}
