<?PHP
/**
 * @package FrontEnds
 * @subpackage Auth
 */
include_once('config.php');
include_once($cfg['MVC']['dir']['root'] . '/Page.class.php');
include_once($cfg['Auth']['dir']['root'] . '/AuthUtil.class.php');

MVCUtils::includeViewer('ExceptionViewer', 'MVC');

$c = new Page();

?>