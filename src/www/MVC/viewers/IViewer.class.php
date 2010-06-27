<?php
/**
 * 
 * @package MVC
 */

/**
 * Defines requirements for any Viewer objects
 */
interface IViewer {
	
	/**
	 * Should print the template
	 */
	public function printTemplate();
	
	/**
	 * Should return the rendered template code
	 */
	public function getCode();
	
	
}