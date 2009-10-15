<?php
/**
* @version		$Id: toolbar.modules.php 10381 2008-06-01 03:35:53Z pasamio $
* @package		Joomla
* @subpackage	Modules
* @copyright	Copyright (C) 2005 - 2008 Open Source Matters. All rights reserved.
* @license		GNU/GPL, see LICENSE.php
* Joomla! is free software. This version may have been modified pursuant
* to the GNU General Public License, and as distributed it includes or
* is derivative of works licensed under the GNU General Public License or
* other free or open source software licenses.
* See COPYRIGHT.php for copyright notices and details.
*/

// no direct access
defined( '_JEXEC' ) or die( 'Restricted access' );

require_once( JApplicationHelper::getPath( 'toolbar_html' ) );

$client	=& JApplicationHelper::getClientInfo(JRequest::getVar('client', '0', '', 'int'));

switch ($task) {

	case 'editA':
	case 'edit':
		TOOLBAR_modules::_EDIT( $client );
		break;

	case 'add':
		TOOLBAR_modules::_NEW($client);
		break;

	default:
		TOOLBAR_modules::_DEFAULT($client);
		break;
}