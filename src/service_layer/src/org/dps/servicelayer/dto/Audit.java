package org.dps.servicelayer.dto;

import java.util.Date;

import javax.persistence.Column;
import javax.persistence.MappedSuperclass;
import javax.persistence.Version;

import org.hibernate.annotations.Generated;
import org.hibernate.annotations.GenerationTime;

@MappedSuperclass
public abstract class Audit {
	
	@Column(name="last_modified")
	@Version()
	//@Generated(GenerationTime.ALWAYS)
	private Long lastUpdated = new Date().getTime();

	/**
	 * @return the lastUpdated
	 */
	public Long getLastUpdated() {
		return lastUpdated;
	}
	/**
	 * @param lastUpdated the lastUpdated to set
	 */
	public void setLastUpdated(Long lastUpdated) {
		this.lastUpdated = lastUpdated;
	}

}
