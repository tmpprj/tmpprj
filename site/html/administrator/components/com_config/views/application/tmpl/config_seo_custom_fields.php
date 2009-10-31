<?php 
defined('JPATH_BASE') or die();
?>
<fieldset class="adminform">
	<legend><?php echo JText::_( 'Custom fields SEO' ); ?></legend>

	<table class="admintable" cellspacing="1" width="100%">

		<tbody>
			<tr>
				<th><?php echo JText::_( 'META tag name' ); ?></th>
				<th><?php echo JText::_( 'Field input label' ); ?></th>
				<th><?php echo JText::_( 'Description of the META tag' ); ?></th>
			</tr>
			<?php echo $lists['custom_fields']; ?>
			<tr>
				<td colspan="3" align="left"><br/><?php echo JText::_( '(You can add custom META tag fields within your metadata.xml file in your server root)' ); ?></td>
			</tr>
		</tbody>
	</table>
</fieldset>
