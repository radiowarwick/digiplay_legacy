package org.dps.servicelayer.dto;

import java.util.List;

import javax.persistence.Column;
import javax.persistence.Entity;
import javax.persistence.GeneratedValue;
import javax.persistence.GenerationType;
import javax.persistence.Id;
import javax.persistence.JoinColumn;
import javax.persistence.ManyToOne;
import javax.persistence.OneToMany;
import javax.persistence.Table;

import org.hibernate.annotations.Sort;
import org.hibernate.annotations.SortType;

@Entity
@Table(name="cartset")
public class Cartset extends Audit  {
	
	@Column(name="cartset_id")
	@Id
	@GeneratedValue(strategy=GenerationType.AUTO)
	private Long cartsetID;
	
	@Column(name="name")
	private String name;
	
	@Column(name="description")
	private String description;
	
	@ManyToOne
	@JoinColumn(name="file_id")
	private File file;
	
	@OneToMany
	@JoinColumn(name="cartset_id")
	@Sort(type = SortType.COMPARATOR, comparator = CartwallPageComparator.class)
	private List<Cartwall> cartwalls;
	
	public Long getCartsetID() {
		return cartsetID;
	}

	public void setCartsetID(Long cartsetID_) {
		cartsetID = cartsetID_;
	}

	public String getName() {
		return name;
	}

	public void setName(String name_) {
		name = name_;
	}

	public String getDescription() {
		return description;
	}

	public void setDescription(String description_) {
		description = description_;
	}

	public File getFile() {
		return file;
	}

	public void setFile(File file_) {
		file = file_;
	}

	public List<Cartwall> getCartwalls() {
		return cartwalls;
	}

	public String toString() {
		return name;
	}
}
