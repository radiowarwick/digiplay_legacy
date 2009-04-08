package org.dps.servicelayer.dto;

import org.slf4j.Logger;
import org.slf4j.LoggerFactory;

public class Privilage extends Audit {

	final static Logger LOGGER = LoggerFactory.getLogger(Privilage.class);
	
	private Long privilageID;
	private String name;
	private String description;
}
