<?php
/**
* @version		$Id: mod_footer.php 10381 2008-06-01 03:35:53Z pasamio $
* @package		Joomla
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

$version = new JVersion();

?>
<div>
	<?php echo $version->URL; ?>
</div>

<div class="smallgrey">
	<?php echo $version->getLongVersion(); ?>
</div>

<div>
	<a href="http://www.joomla.org/content/blogcategory/32/66/" target="_blank"><?php echo JText::_( 'Check for latest Version' ); ?></a>
</div>