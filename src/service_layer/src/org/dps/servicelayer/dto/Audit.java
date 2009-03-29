package org.dps.servicelayer.dto;

import javax.persistence.Column;

public abstract class Audit {
	
	@Column(name="last_modified")
	private int lastUpdated;

	
	/**
	 * @return the lastUpdated
	 */
	public int getLastUpdated() {
		return lastUpdated;
	}
	/**
	 * @param lastUpdated the lastUpdated to set
	 */
	public void setLastUpdated(int lastUpdated) {
		this.lastUpdated = lastUpdated;
	}

}
